#ifndef __EVENT_H__
#define __EVENT_H__

void Display (void);
void Reshape (int, int);
void Timer (int value);
void NpcTimer (int value);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int b, int s, int x, int y);

#endif /* __EVENT_H__ */
