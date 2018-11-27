#ifndef __LCD_COMMON_H__
#define __LCD_COMMON_H__

#define LCD_SERVER_PORT     (1116)

#define LCD_MSG_LENGTH      (16 + 1)
#define LCD_MSG_STRING_END  '\0'

#define LCD_MSG_LOGIN       "REGX"
#define LCD_MSG_SEND        "MSGX"
#define LCD_MSG_LIGHTON     "LONX"
#define LCD_MSG_LIGHTOFF    "LOFF"
#define LCD_MSG_CLEAR       "CLRX"
#define LCD_MSG_STOPIT      "STOP"
#define LCD_MSG_RESTART     "RSTX"
#define LCD_MSG_DEBUG       "DBGX"

#endif // __LCD_COMMON_H__
