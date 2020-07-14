#ifndef DRAW_LINKAGE_H_INCLUDED
#define DRAW_LINKAGE_H_INCLUDED

void init_linkage();
void calculate_static_parts();
void draw_five_bar_linkage(float th1, float th4);
void draw_base_of_linkage();
void draw_line(struct MyPOINT p1, struct MyPOINT p2);
void calculate_inverse_kinematics(float x, float y, float* buf);
float map_between(float x, float in_min, float in_max, float out_min, float out_max);

#endif // !DRAW_LINKAGE_H_INCLUDED
