#define TRAV_FRAMES_MIN 2
#define TRAV_FRAMES_MAX 40
#define TRAV_FRAMES_DELTA 5

#define RENDER_DELAY 100
#define GREY_LEVEL 16

typedef struct {
  float pos;
  int8_t vel;
} t_travAxis;

typedef struct {
  t_travAxis axisx;
  t_travAxis axisy;
  t_travAxis axisz;
} t_travCube;
