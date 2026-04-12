// https://github.com/microsoft/RustTraining/blob/main/rust-patterns-book/src/ch17-exercises.md
// import things to remember:
//  - close all sender, so receiver can got proper END state
//  - using Arc/Mutex, to cross thread for a non-sendable type
//  - always join thread handle in main thread

// ### Exercise 3: Channel-Based Worker Pool ★★★ (~45 min)
//
// Build a worker pool using channels where:
// - A dispatcher sends `Job` structs through a channel
// - N workers consume jobs and send results back
// - Use `crossbeam-channel` (or `std::sync::mpsc` if crossbeam is unavailable)

use std::sync::mpsc;
use std::sync::Arc;
use std::sync::Mutex;
use std::thread;

struct Job {
    id: u64,
    data: String,
}

#[derive(Debug)]
struct JobResult {
    job_id: u64,
    output: String,
    worker_id: usize,
}

fn worker_pool(jobs: Vec<Job>, num_workers: usize) -> Vec<JobResult> {
    // Create an asynchronous channel
    let (job_tx, job_rx) = mpsc::channel::<Job>();
    let (result_tx, result_rx) = mpsc::channel::<JobResult>();
    // ! receiver is not sendable
    let job_rx = Arc::new(Mutex::new(job_rx));

    let mut handles = vec![];
    for worker_id in 0..num_workers {
        // ! this clone is need to move job_rx in
        let job_rx = job_rx.clone();
        let result_tx = result_tx.clone();
        handles.push(thread::spawn(move || {
            loop {
                let job = {
                    let rx = job_rx.lock().unwrap();
                    rx.recv() // block until a job or channel closes
                };
                match job {
                    Ok(job) => {
                        let output = format!("processed '{}' by worker {worker_id}", job.data);
                        result_tx
                            .send(JobResult {
                                job_id: job.id,
                                output,
                                worker_id,
                            })
                            .unwrap();
                    }
                    Err(_) => {
                        break; // channel closed
                    }
                }
            }
        }));
    }

    // !todo: why needed?
    // Rust 的 mpsc 通道规则：
    // 只有当所有发送端（result_tx）都被销毁时，接收端 result_rx.recv() / for res in result_rx 才会返回错误 / 结束循环。
    drop(result_tx); // Drop our copy so result channel closes when workers finish

    let job_len = jobs.len();
    for job in jobs {
        job_tx.send(job).unwrap();
    }
    // !see same drop above
    drop(job_tx); // close job channel

    let mut results = vec![];
    for result in result_rx {
        results.push(result);
    }
    assert_eq!(results.len(), job_len);

    // ! thread must be joined
    // if result_tx didn't drop in main thread, this will hang forever
    for h in handles {
        h.join().unwrap();
    }

    return results;
}

fn main() {
    let jobs = vec![
        Job {
            id: 1,
            data: "new".into(),
        },
        Job {
            id: 1,
            data: "new".into(),
        },
    ];

    let results = worker_pool(jobs, 2);
    for r in &results {
        println!("[worker {}] job {}: {}", r.worker_id, r.job_id, r.output);
    }
}
