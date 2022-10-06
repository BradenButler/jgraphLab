//Braden Butler
//COSC 494
//golfgraph.cpp
//program to create .jgr file for Jgraph lab
//takes .txt file as input
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include <unistd.h>
using namespace std;

class Golfer {
    public:
    string name;
    double OTT;     //Off-the-tee
    double APG;     //Approach-the-green
    double ARG;     //Around-the-green
    double PUT;     //Putting
    double total;
    int rank;       //order

    Golfer() {
        OTT=-999;
        APG=-999;
        ARG=-999;
        PUT=-999;
        total=0;
        rank=0;
    }
};

int main(int argc, char **argv) {
    //file pointer
    FILE *fp;
    //golfer instance
    Golfer *g;
    string filename;
    //map of golfers
    map<string, Golfer*> Golfers;
    multimap<double, Golfer*> SortGolfers;
    //golfer map iterator
    map<string, Golfer*>::iterator it;
    multimap<double, Golfer*>::iterator it2;
    //temp first name
    char first[80];
    //temp last name
    char last[80];
    //current value being read from file
    double value;
    //name temp
    string name;
    //generic iterator
    double i=0;
    int k=0;
    double xoffset=0;
    double yoffset=0;
    //keep track of bar position pos and neg
    double negPos=0;
    double posPos=0;
    //colors
    double red[3] = {1, .5, 0};
    double orange[3] = {1, .2, 0};
    double green[3] = {0, .6, .2};
    double blue[3] = {0, .2, .8};

    double lred[3] = {1, .6, .8};
    double lorange[3] = {1, .8, .6};
    double lgreen[3] = {.6, 1, .6};
    double lblue[3] = {.6, .8, 1};

//read from the golf stat file
    fp = fopen(argv[1], "r");

//Read through the file
    while(1) {
        if(fscanf(fp, "%s %s %lf", first, last, &value)==EOF) {
            break;
        }
//build name
        name+=first;
        name+=" ";
        name+=last;
//check for name
        it=Golfers.find(name);
//golfer is not here, add him
        if(it==Golfers.end()) {
            g = new Golfer;
            g->name = name;
            g->OTT = value;
            g->total+=value;
            Golfers.insert(std::pair<string, Golfer*>(name, g));
            //cout << name << endl;
//golfer is here, add the data.
        } else {
            it->second->total+=value;
            if(it->second->APG==-999) it->second->APG=value;
            else if(it->second->ARG==-999) it->second->ARG=value;
            else if(it->second->PUT==-999) it->second->PUT=value;
        }

        //cout << name << " " << value << endl;
        name="";
    }

    for(it=Golfers.begin();it!=Golfers.end();it++) {
        SortGolfers.insert(std::pair<double, Golfer*>(it->second->total, it->second));
    }

    fclose(fp);

//build the jgraph file
    fp= fopen("jtest.jgr", "w+");
//header and axis information
    fprintf(fp, "newgraph\n");
    fprintf(fp, "xaxis min -20 max 25 size 2\n"); //size 5
    fprintf(fp, "grid_lines grid_gray .7\n");
    fprintf(fp, "yaxis min 0 max 5 hash 0 mhash 0 size 1\n"); //size 2.5


//the squares...
    k=0;
    int j=1;
    i=1;
    for(it2=SortGolfers.begin();it2!=SortGolfers.end();it2++) {

        if((k%5==0)&&(k!=0)) {
            fprintf(fp, "copygraph\n");
            xoffset+=2.5;
            fprintf(fp, "x_translate %lf\n", xoffset);
            if((j%3==0)) {
                yoffset+=-1.5;
                xoffset=0;
                fprintf(fp, "x_translate %lf\n", xoffset);
                fprintf(fp, "y_translate %lf\n", yoffset);
            }
            i=1;
            j++;
        }

        //bar for OTT
        if(it2->second->OTT>0) {
            fprintf(fp, "newline poly linethickness 1 pcfill %lf %lf %lf   color .25 .25 .25\n", red[0], red[1], red[2]);
            fprintf(fp, "pts 0 %lf  %lf %lf  %lf %lf  0 %lf\n", i-.25, it2->second->OTT, i-.25, it2->second->OTT, i+.25, i+.25);
        } else {
            fprintf(fp, "newline poly linethickness 1 pcfill %lf %lf %lf   color .25 .25 .25\n", lred[0], lred[1], lred[2]);
            fprintf(fp, "pts 0 %lf  %lf %lf  %lf %lf  0 %lf\n", i-.25, it2->second->OTT, i-.25, it2->second->OTT, i+.25, i+.25);
        }
        if(it2->second->OTT>0) posPos+=it2->second->OTT;
        else negPos+=it2->second->OTT;


        //bar for APG
        if(it2->second->APG>0) {
            fprintf(fp, "newline poly linethickness 1 pcfill %lf %lf %lf   color .25 .25 .25\n", orange[0], orange[1], orange[2]);
            fprintf(fp, "pts %lf %lf  %lf %lf  %lf %lf  %lf %lf\n", posPos, i-.25, it2->second->APG+posPos, i-.25, it2->second->APG+posPos, i+.25, posPos, i+.25);
        } else {
            fprintf(fp, "newline poly linethickness 1 pcfill %lf %lf %lf   color .25 .25 .25\n", lorange[0], lorange[1], lorange[2]);
            fprintf(fp, "pts %lf %lf  %lf %lf  %lf %lf  %lf %lf\n", negPos, i-.25, it2->second->APG+negPos, i-.25, it2->second->APG+negPos, i+.25, negPos, i+.25);
        }
        if(it2->second->APG>0) posPos+=it2->second->APG;
        else negPos+=it2->second->APG;


        //bar for ARG
        if(it2->second->ARG>0) {
            fprintf(fp, "newline poly linethickness 1 pcfill %lf %lf %lf   color .25 .25 .25\n", green[0], green[1], green[2]);
            fprintf(fp, "pts %lf %lf  %lf %lf  %lf %lf  %lf %lf\n", posPos, i-.25, it2->second->ARG+posPos, i-.25, it2->second->ARG+posPos, i+.25, posPos, i+.25);
        } else {
            fprintf(fp, "newline poly linethickness 1 pcfill %lf %lf %lf   color .25 .25 .25\n", lgreen[0], lgreen[1], lgreen[2]);
            fprintf(fp, "pts %lf %lf  %lf %lf  %lf %lf  %lf %lf\n", negPos, i-.25, it2->second->ARG+negPos, i-.25, it2->second->ARG+negPos, i+.25, negPos, i+.25);
        }

        if(it2->second->ARG>0) posPos+=it2->second->ARG;
        else negPos+=it2->second->ARG;


        //bar for PUT
        if(it2->second->PUT>0) {
            fprintf(fp, "newline poly linethickness 1 pcfill %lf %lf %lf   color .25 .25 .25\n", blue[0], blue[1], blue[2]);
            fprintf(fp, "pts %lf %lf  %lf %lf  %lf %lf  %lf %lf\n", posPos, i-.25, it2->second->PUT+posPos, i-.25, it2->second->PUT+posPos, i+.25, posPos, i+.25);
        } else {
            fprintf(fp, "newline poly linethickness 1 pcfill %lf %lf %lf   color .25 .25 .25\n", lblue[0], lblue[1], lblue[2]);
            fprintf(fp, "pts %lf %lf  %lf %lf  %lf %lf  %lf %lf\n", negPos, i-.25, it2->second->PUT+negPos, i-.25, it2->second->PUT+negPos, i+.25, negPos, i+.25);
        }

        if(it2->second->PUT>0) posPos+=it2->second->PUT;
        else negPos+=it2->second->PUT;

        //names for the golfers
        fprintf(fp, "newstring hjl vjb x %lf y %lf\n", posPos+3, i);
        fprintf(fp, "fontsize 10 font Times : %s\n", it2->second->name.c_str());

        //golfer showing total
        fprintf(fp, "newcurve eps golfer.eps marksize 12 3 pts\n");
        fprintf(fp, "   %lf %lf\n", it2->second->total+4.4, i+1);

        posPos=0;
        negPos=0;
        i++;
        k++;
    }

    //legend stuff
    fprintf(fp, "newcurve marktype box gray 2 cfill %lf %lf %lf marksize 2 .2\nlabel : Tee to Green (Positive)\n", red[0], red[1], red[2]);
    fprintf(fp, "newcurve marktype box gray 2 cfill %lf %lf %lf marksize 2 .2\nlabel : Approach the green (Positive)\n", orange[0], orange[1], orange[2]);
    fprintf(fp, "newcurve marktype box gray 2 cfill %lf %lf %lf marksize 2 .2\nlabel : Arround the green (Positive)\n", green[0], green[1], green[2]);
    fprintf(fp, "newcurve marktype box gray 2 cfill %lf %lf %lf marksize 2 .2\nlabel : Putting (Positive)\n", blue[0], blue[1], blue[2]);

    fprintf(fp, "newcurve marktype box gray 2 cfill %lf %lf %lf marksize 2 .2\nlabel : Tee to Green (Negative)\n", lred[0], lred[1], lred[2]);
    fprintf(fp, "newcurve marktype box gray 2 cfill %lf %lf %lf marksize 2 .2\nlabel : Approach the green (Negative)\n", lorange[0], lorange[1], lorange[2]);
    fprintf(fp, "newcurve marktype box gray 2 cfill %lf %lf %lf marksize 2 .2\nlabel : Arround the green (Negative)\n", lgreen[0], lgreen[1], lgreen[2]);
    fprintf(fp, "newcurve marktype box gray 2 cfill %lf %lf %lf marksize 2 .2\nlabel : Putting (Negative)\n", lblue[0], lblue[1], lblue[2]);
    fprintf(fp, "legend y -1.25\n");

    fclose(fp);
//run jgraph to generate the graph from the .jgr file
    system("/home/jplank/bin/LINUX-X86_64/jgraph  -P jtest.jgr | ps2pdf - | convert -density 300 - -quality 100 golf_stats.jpg");

    return 0;
}

