#ifndef PXCOUNT_H
#define PXCOUNT_H

class pxcount{
      private:
            int cellsx, cellsy;
            float pxWidth, pxHeight;
      public:
        pxcount(int numcellsx, int numcellsy, float pxWidth, float pxHeight);
        ~pxcount() = default;
        void setCells(int numcellsx, int numcellsy);
        void setPx(int numcellsx, int numcellsy,float pxWidth, float pxHeight);
        float getPxWidth();
        float getPxHeight();
};

#endif
