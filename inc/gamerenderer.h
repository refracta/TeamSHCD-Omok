#define RG_BLACK u8"●"
#define RG_WHITE u8"○"

#define RG_GRID_TYPE_1 u8"└"
#define RG_GRID_TYPE_2 u8"┴"
#define RG_GRID_TYPE_3 u8"┘"
#define RG_GRID_TYPE_4 u8"├"
#define RG_GRID_TYPE_5 u8"┼"
#define RG_GRID_TYPE_6 u8"┤"
#define RG_GRID_TYPE_7 u8"┌"
#define RG_GRID_TYPE_8 u8"┬"
#define RG_GRID_TYPE_9 u8"┐"
#define RG_GRID_TYPE_H u8"─"
#define RG_GRID_TYPE_V u8"│"

void render_grid(char** grid, int width, int height);
char* generate_grid_string(char** grid, int width, int height);
void draw_grid(int x, int y, char** grid, short** stone_colors, int width, int height, short grid_color);