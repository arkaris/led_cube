typedef struct {
  uint8_t pos;
  int8_t vel;
  uint8_t frame;
} t_travAxis;

typedef struct {
  t_travAxis axisx;
  t_travAxis axisy;
  t_travAxis axisz;
} t_travCube;

#define TRAV_FRAMES_MIN 1
#define TRAV_FRAMES_MAX 50
