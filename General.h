// Packet types.
#define STATUS          0 // Status information.
#define TASK_SELF       1 // The self task.
#define TASK_REQ        2 // The task request.
#define TASK_COMP       3 // Self timer for timing the computation of task.
#define TASK_RESP       4 // The task response.
#define PRINT_STATUS    5 // The status printing timer.

#define MAX_CM          2000
#define MAX_SENSORS     2
#define EACH_CM_GROUP   512

#define ID_INDEX        1000

#define MB_TO_BIT       (1024 * 1024 * 8)

#define STATUS_PAR      "status"
#define TASK_PAR        "task"
