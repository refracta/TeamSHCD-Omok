/**
 * @brief 콘솔에서 사용하는 색깔 열거형
 */
typedef enum
{
	BLACK, BLUE, GREEN, JADE, RED, PURPLE, YELLOW, WHITE, GRAY,
	LIGHT_BLUE, LIGHT_GREEN, LIGHT_JADE, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, LIGHT_WHITE
} ConsoleColor;

void set_cursor_visibility(bool);
void set_cursor_position(int, int);
void set_print_color(int, int);
void clear_console();
int get_key_input();
int wait_with_handler(unsigned long, int (*)(int));
void xyprint(int, int, char *, ...);
