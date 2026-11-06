             Batch Jobs
                  |
                  v
             Job Queue
                  |
          Shared Atomic Index
                  |
       +----------+----------+
       |          |          |
       v          v          v
   Worker 1   Worker 2   Worker 3
       |          |          |
       v          v          v
    Result 1   Result 2   Result 3
       |          |          |
       +----------+----------+
                  |
                  v
             Final Results
