//Code provided as part of CS 154 Lab 5, Feb 2020
//made available only for study purposes
//to students and TAs of the lab
//retain this header in your submission
//given code improved by: ..... write your name here


#include <iostream>
#include <cstdlib>
#include <fstream>   
#include <cstdlib>
#include <fstream>   
#include <string.h>

#include <FL/Fl.H>				
#include <FL/Fl_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
using namespace std;

void click(Fl_Widget*p, void * w) {

	int atno = *((int*)w);                               //atno variable is created in which void w is converted to int & then assigned to atno
	static Fl_Window *window;               // Hides the previous window to avoid mess
	int i,j;
	i=atno-1;
	string B = "\n";                                  //B is created to change line
	string C = "";
	string D[10];
	D[0]="Atomic No. = ";
	D[1]="Name = ";                                 
	D[2]="Symbol = ";
	D[3]="Group No. = ";
	D[4]="Period No. = ";
	D[5]="Block = ";
    D[6]="State = ";
	D[7]="Occurance = ";
	D[8]="Type = ";
	D[9]="Input Code supplied for CS 154 Lab";
	fstream f;
	f.open("table");                                   //opens file &takes input from it
    string A[118][9];

	for(int ii=0;ii<118;ii++){
		for(int jj=0;jj<9;jj++){                   //data from file is stored in 2D string array
        		f>>A[ii][jj];
		}
	}
       
	for(int jj=0;jj<9;jj++)
		C=C+D[jj]+A[i][jj]+B;                     //all data is collected in new string array C
		
	C=C+B+B+B+D[9];
	
	delete window;
	window = new Fl_Window (0,0,550,500,A[i][1].data());	//new window is created with name of element as heading
 	window->color (FL_WHITE);
 		
	Fl_Box *b1;
	b1 = new Fl_Box (0,0,550,500,C.data());                       //data stored in C is displayed on window
	b1->box(FL_FLAT_BOX);
	b1->labelsize(25);	                                       //label size is chosen
	b1->color (99);		                                       //color is chosen

	window->end();			                       
 	window->show();

 	Fl::run();
			
    }

int main (int argc, char *argv[]) {

	Fl_Window *window = new Fl_Window (1080,540);	                       //main window is created to display table
 		window->color (FL_WHITE);		

	int *atno;                                                         //array is created to have a pointer to each button
	atno=new int [121];

	for (int abc=0; abc<121; abc++) atno[abc]=abc+1;

	string A[121];                                   //string array A is created to combine two different array
	string B[121];                                   //string array B is created to take atomic numbers from file atno
	string C[121];                                   //string array B is created to take symbols of elements 
	string a="\n ";
	string D[17];
	string E[18];
	ifstream f,m,g,h,l;                             //input files are created
	f.open("symbol");
	g.open("atno");
	h.open("pt1");
	l.open("pt2");

	for (int i=0; i<120; i++) { 
			f >> C[i];                      //symbols are stored in array C
			g >> B[i];                     // atomic no's are stored in B
			A[i]=B[i]+a+C[i];    		   //B & c are combined
	}

	for (int i=2; i<17; i++) 
			h >> D[i];

	for (int i=2; i<8; i++) 
			l >> E[i];

	Fl_Button *button[18][9];                      //buttons are created each having specific identity

	button[0][0] = new Fl_Button (0,0,60,60,A[0].data());             //A[0] i.e.about hydrogen is written on button
		button[0][0]->color (6);
		button[0][0]->callback(click, (void*)(atno+0));           //callback function is called after clicking 1st button
		
	button[17][0] = new Fl_Button (17*60,0,60,60,A[1].data());        //intermediate buttons are not called back as they are of no use & direct button[17][0]is called
		button[17][0]->color (6);
		button[17][0]->callback(click, (void*)(atno+0+1));	

	for (int i=1;i<17;++i) {
		button[i][0] = new Fl_Button (i*60,0,60,60,D[i-1].data());	//intermediate blocks between H & He are given white color
		button[i][0]->color (FL_WHITE);	}	

	for (int i=0;i<2;i++){
		button[i][0] = new Fl_Button (i*60,60,60,60,A[2+i].data());	//Li & Be are printed on buttons & given distinct color
		button[i][0]->color (6);
		button[i][0]->callback(click, (void*)(atno+i+2));        //pointer is provided to buttons which contains no equal to atomic no of element which is clicked
	                     }

	for (int i=2;i<12;i++){
		button[i][1] = new Fl_Button (i*60,60,60,60,E[i-2].data());	//intermediate blocks between Be & B are given white color
		button[i][1]->color (FL_WHITE);
	                      
				}

	for (int i=12;i<18;i++){
		button[i][1] = new Fl_Button (i*60,60,60,60,A[i-8].data());	//B to Ne are are printed on buttons
		button[i][1]->color (6);
		button[i][1]->callback(click, (void*)(atno+i-8));
				}

	for (int i=0;i<2;i++){
		button[i][2] = new Fl_Button (i*60,2*60,60,60,A[10+i].data());	//Na & Mg are printed on buttons & given distinct color
		button[i][2]->color (6);
		button[i][2]->callback(click, (void*)(atno+i+10));	//pointer is provided to buttons which contains no equal to atomic no of element which is clicked
	                     }

	for (int i=2;i<12;i++){
		button[i][2] = new Fl_Button (i*60,2*60,60,60);	
		button[i][2]->color (FL_WHITE);
	                      }

	for (int i=12;i<18;i++){
		button[i][2] = new Fl_Button (i*60,2*60,60,60,A[i].data());	
		button[i][2]->color (6);
		button[i][2]->callback(click, (void*)(atno+i));		//pointer is provided to buttons which contains no equal to atomic no of element which is clicked
		}

	for (int i=0;i<2;i++){						//K & Ca are printed on buttons & given distinct color
		button[i][3] = new Fl_Button (i*60,3*60,60,60,A[18+i].data());	
		button[i][3]->color (6);
		button[i][3]->callback(click, (void*)(atno+i+18)); 
	                     }

	for (int i=2;i<12;i++){
		button[i][3] = new Fl_Button (i*60,3*60,60,60,A[18+i].data());	
		button[i][3]->color (69);
		button[i][3]->callback(click, (void*)(atno+i+18)); 	//pointer is provided to buttons which contains no equal to atomic no of element which is clicked
	                      }

	for (int i=12;i<18;i++){
		button[i][3] = new Fl_Button (i*60,3*60,60,60,A[i+18].data());	
		button[i][3]->color (6);
		button[i][3]->callback(click, (void*)(atno+i+18));	//pointer is provided to buttons which contains no equal to atomic no of element which is clicked
	                       }

	for (int i=0;i<2;i++){						//Rb & Sr are printed on buttons & given distinct color
		button[i][4] = new Fl_Button (i*60,4*60,60,60,A[18+18+i].data());	
		button[i][4]->color (6);
		button[i][4]->callback(click, (void*)(atno+i+36));	//pointer is provided to buttons which contains no equal to atomic no of element which is clicked
	                     }

	for (int i=2;i<12;i++){
		button[i][4] = new Fl_Button (i*60,4*60,60,60,A[18+18+i].data());	
		button[i][4]->color (69);
		button[i][4]->callback(click, (void*)(atno+i+36)); 	//pointer is provided to buttons which contains no equal to atomic no of element which is clicked
	                      }

	for (int i=12;i<18;i++){
		button[i][4] = new Fl_Button (i*60,4*60,60,60,A[i+18+18].data());	
		button[i][4]->color (6);
		button[i][4]->callback(click, (void*)(atno+i+36));	//pointer is provided to buttons which contains no equal to atomic no of element which is clicked
	                       }

	for (int i=0;i<2;i++){						//Cs & Ba are printed on buttons & given distinct color
		button[i][5] = new Fl_Button (i*60,5*60,60,60,A[18+i+36].data());	
		button[i][5]->color (6);
		button[i][5]->callback(click, (void*)(atno+i+54));	//pointer is provided to buttons which contains no equal to atomic no of element which is clicked
	                      }

	for (int i=2;i<12;i++){
		button[i][5] = new Fl_Button (i*60,5*60,60,60,A[18+i+36].data());	
		button[i][5]->color (69);
		if(i!=2)button[i][5]->callback(click, (void*)(atno+i+68));//pointer is provided to buttons which contains no equal to atomic no of element which is clicke
	                      }

	for (int i=12;i<18;i++){
		button[i][5] = new Fl_Button (i*60,5*60,60,60,A[i+18+18+18].data());	
		button[i][5]->color (6);
		button[i][5]->callback(click, (void*)(atno+i+68));	//pointer is provided to buttons which contains no equal to atomic no of element which is clicked
	                       }

	for (int i=0;i<2;i++){						//Fr & Ra are printed on buttons & given distinct color
		button[i][6] = new Fl_Button (i*60,6*60,60,60,A[18+18+i+36].data());	
		button[i][6]->color (6);
		button[i][6]->callback(click, (void*)(atno+i+86));	//pointer is provided to buttons which contains no equal to atomic no of element which is clicked
	                     }

	for (int i=2;i<12;i++){
		button[i][6] = new Fl_Button (i*60,6*60,60,60,A[18+18+i+36].data());	
		button[i][6]->color (69);
		if(i!=2)button[i][6]->callback(click, (void*)(atno+i+100));	//pointer is provided to buttons which contains no equal to atomic no of element which 										//is clicked
	                      }
	                      

	for (int i=12;i<18;i++){
		button[i][6] = new Fl_Button (i*60,6*60,60,60,A[18+i+18+18+18].data());	
		button[i][6]->color (6);
		button[i][6]->callback(click, (void*)(atno+i+100));	//pointer is provided to buttons which contains no equal to atomic no of element which is clicked
	                       }

	for (int i=0;i<2;i++){						//The 2nd last row 1st 2 blocks are created & given distinct color white
		button[i][7] = new Fl_Button (i*60,7*60,60,60);	
		button[i][7]->color (FL_WHITE);
	                     }

	for (int i=2;i<17;i++){
		button[i][7] = new Fl_Button (i*60,7*60,60,60,A[16+18+18+i+36].data());	
		button[i][7]->color (85);
		button[i][7]->callback(click, (void*)(atno+i+54));	//pointer is provided to buttons which contains no equal to atomic no of element which is clicked
	                      }

	for (int i=17;i<18;i++){
		button[i][7] = new Fl_Button (i*60,7*60,60,60);	
		button[i][7]->color (FL_WHITE);
	                        }

	for (int i=0;i<2;i++){						//The fimal row 1st 2 blocks are created & given distinct color white
		button[i][8] = new Fl_Button (i*60,8*60,60,60);	
		button[i][8]->color (FL_WHITE);
	                      }

	for (int i=2;i<17;i++){
		button[i][8] = new Fl_Button (i*60,8*60,60,60,A[10+5+16+18+18+i+36].data());	
		button[i][8]->color (85);
		button[i][8]->callback(click, (void*)(atno+i+32+54));	//pointer is provided to buttons which contains no equal to atomic no of element which is clicked
	                      }

	for (int i=17;i<18;i++){
		button[i][8] = new Fl_Button (i*60,8*60,60,60);	
		button[i][8]->color (FL_WHITE);
				}


	 window->end();			
	 window->show();
					
	 for(int i=0; i<50; i++) Fl::wait();			

}