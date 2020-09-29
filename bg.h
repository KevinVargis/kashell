#ifndef __BG_H
#define __BG_H

void jobs();
void add_bg(char* args[], int pid);
void del_bg(int pno);
void bg(int pno);
void overkill();

#endif