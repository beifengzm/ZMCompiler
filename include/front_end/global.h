#define STATE_START  0
#define STATE_KEY_ID 1   // keyword or identifier
#define STATE_NUM 2   
#define STATE_COMMIT1 3  // 单斜杠 /
#define STATE_COMMIT2 4  // 单斜杠 //
#define STATE_COMMIT3 5  // 单斜杠 /*
#define STATE_COMMIT4 6  // 双斜杠 /* *
#define STATE_STRING 7   // 字符串
#define STATE_SYMBOL 8