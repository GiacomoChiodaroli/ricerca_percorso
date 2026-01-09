#include "pxcount.h"
pxcount::pxcount(int numcellsx, int numcellsy, float pxWidth, float pxHeight) {
   setCells(numcellsx, numcellsy);
   setPx(numcellsx, numcellsy, pxWidth, pxHeight);
};

void pxcount::setCells(int numcellsx, int numcellsy) {
  cellsx = numcellsx;
  cellsy = numcellsy;
};


void pxcount::setPx(int numcellsx, int numcellsy, float pxPerX, float pxPerY) {
  pxWidth = pxPerX/numcellsx;
  pxHeight = pxPerY/numcellsy;
};

float pxcount::getPxWidth() {return pxWidth;};
float pxcount::getPxHeight() {return pxHeight;};