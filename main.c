#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "shell.h"

#define GUESSES 15
#define ALLREADY 1111
#define NOWORD  1222
#define ALLREADY 1111
#define NOWORD  1222

int check_guess();
int check_for_buffs();
int sizes[]={137,193,199,195,63,166,155,157,41,68,93,179,158,79,85,200,14,152,278,182,33,64,140,1,63,25};
gchar Guesss_word[5], Guessed_word[5], n=0;
 int COWS, BUFFS, NO;
 gchar entries[16][6];
 
 int load_word()
{
       
    FILE *f1;
    char sfa[6];
    int a;
    n=0;
    srand(time(NULL));
    a=rand()%26;
    printf("%d \n",a+1);
    sfa[0]=a+'a';
    sfa[1]='.';
    sfa[2]='t';  sfa[3]='x'; sfa[4]='t';
    sfa[5]='\0';
    printf("%s \n",sfa);
     f1=fopen(sfa,"r");
     a=rand()%sizes[a];
    fscanf(f1,"%s",Guesss_word);
     a--; 
     while(a--)
    fscanf(f1,"%s",Guesss_word);
     printf("%s\n",Guesss_word);
     NO=15;
     COWS=BUFFS=0;
     fclose(f1);
     return 0;
}

 int Full_check()
{
    int i, check=0;
     FILE *f1;
    char sfa[6], temp[10];
    
    sfa[0]=Guessed_word[0];
    sfa[1]='.';
    sfa[2]='t';  sfa[3]='x'; sfa[4]='t';
    sfa[5]='\0';
    
    for(i=0;i<n;i++)
        if(strcmp(entries[i],Guessed_word)==0)
            return ALLREADY;
      f1=fopen(sfa,"r");      
     for(i=0;i<sizes[Guessed_word[0]-'a'];i++) 
     {
            fscanf(f1,"%s",temp);
            if(strcmp(temp,Guessed_word)==0)
                check=1;
     }
      fclose(f1);
       if(check == 0)
          return  NOWORD;    
      
 for(i=0;i<4;i++)
        Guessed_word[i]=tolower(Guessed_word[i]);
  
    check_for_buffs();
   
        
      strcpy(entries[n],Guessed_word);
      n++;  
    if(check_guess() == 1)
       return 1;
   return 0; 
}

int check_guess()
{
    int i;
    for(i=0;i<4;i++)
      { 
          if(Guessed_word[i] != Guesss_word[i])
           { NO--; return 0; }
      }
     NO--;   
    return 1;       
}

int check_for_buffs()
{
    int i, j;
    BUFFS=0;
     for(i=0,COWS=0;i<4;i++)
         if(Guessed_word[i] == Guesss_word[i])
             COWS++;
     for(i=0;i<4;i++)
     {
        for(j=0;j<4;j++)
          if(Guessed_word[i] == Guesss_word[j] && i != j)
             BUFFS++;
     }
     return 1;
}





#define NAME_OR_PATH_OF_UI_FILE "COWSANDBULLS.glade"
struct _Data{
    
    //Enter The Widgets to be obtained
    GtkTextBuffer  *textbuffer;
    GtkDialog * messagedialog1,*messagedialog2;
    GtkEntryBuffer  *Filepath;
    GtkDrawingArea *DrawArea;
    GtkLabel* Cows,*Bulls,*instruction;
    GtkImage* l[4];
    GtkButton* enterbutton;
    GtkWidget* help,*about;
    GtkWindow *window;
    };
typedef struct _Data Data;
 
Data        data;

gchar instru[]="Enter your four letter guess word below and click Enter Guess.Note: You have have only 15 guess left  to guess the word";
  
void resetgame()
{
     int i;
     char win[4][10];
     for(i=0;i<4;i++)
               {    sprintf(win[i],"%c.png",'_');
                   
                    gtk_image_set_from_file(data.l[i],win[i]);
           }
    load_word();
    gtk_label_set_text(data.Cows,"Cows: 0");
    gtk_label_set_text(data.Bulls,"Bulls: 0");
    sprintf(instru,"Enter your four letter guess word below and click Enter Guess\n.Note: You have have only 15 guess left  to guess the word");
    gtk_label_set_text(data.instruction,instru);
    gtk_text_buffer_set_text (data.textbuffer,"Guessed Words:\n",strlen("Guessed Words:\n"));
    gtk_entry_buffer_set_text(data.Filepath,"",strlen(""));
    load_word();
    
    }
G_MODULE_EXPORT void
helpopen(GtkWidget* w,gpointer s)
{  

 
    gtk_widget_show(data.help);
     
    }
 

G_MODULE_EXPORT void
helpclose(GtkWidget* w,gpointer s)
{   
gtk_widget_hide(data.help);


}

G_MODULE_EXPORT void
aboutopen(GtkWidget* w,gpointer s)
{  

 
    gtk_widget_show(data.about);
     
    }

G_MODULE_EXPORT void
aboutclose(GtkWidget* w,gpointer s)
{    
gtk_widget_hide(data.about);

    }
 
G_MODULE_EXPORT void
HelpWindow(GtkWidget* w,gpointer s)
{
    
    
    }
    
G_MODULE_EXPORT void
Openinternet1(GtkWidget* w,gpointer s)
{   gtk_widget_hide(data.messagedialog1);
   openqtapplication(Guesss_word);
    }

G_MODULE_EXPORT void
Openinternet2(GtkWidget* w,gpointer s)
{   gtk_widget_hide(data.messagedialog2);
    openqtapplication(Guesss_word);
    }

G_MODULE_EXPORT void
closemessagebox1(GtkWidget* w,gpointer s)
{   gtk_widget_hide(data.messagedialog1);
    
    }

G_MODULE_EXPORT void
closemessagebox2(GtkWidget* w,gpointer s)
{   gtk_widget_hide(data.messagedialog2);
    
    }


G_MODULE_EXPORT void
EnterGuessword(GtkWidget* w,gpointer s)
{
    int check,i;
     char str[2000], cowaa[100], bull[100];
     if(!strcmp(gtk_button_get_label(data.enterbutton),"Restart Game"))
     {
        resetgame();
        
        gtk_button_set_label(data.enterbutton,"Enter Guess"); 
         return;   
         }
       if(NO > 0)  
    if(!strcmp(gtk_entry_buffer_get_text(data.Filepath),"") || strlen(gtk_entry_buffer_get_text(data.Filepath))!=4) return;
     if(NO > 0)
   {  
       strcpy(Guessed_word,gtk_entry_buffer_get_text(data.Filepath));
       
       strlwr(Guessed_word);
       gtk_entry_buffer_delete_text(data.Filepath,0,strlen(gtk_entry_buffer_get_text(data.Filepath)));
        if(strcmp(Guessed_word,"ccea")==0)
         { 
             sprintf(instru,"Answer is %s\n",Guesss_word);
             gtk_label_set_text(data.instruction,instru);
             return ;
         }
          if(strcmp(Guessed_word,"caah")==0)
         { 
             sprintf(instru,"The first letter is %c\n",Guesss_word[0]);
             gtk_label_set_text(data.instruction,instru);
             return ;
         }
         if(!isalpha(Guessed_word[0]))
              {
              sprintf(instru,"No such word\nNote: You have have only %d guess left  to guess the word",NO); 
           gtk_label_set_text(data.instruction,instru);
           return;
         } 
       check=Full_check();
         if(check == NOWORD)
         {
              sprintf(instru,"No such word\nNote: You have have only %d guess left  to guess the word",NO); 
           gtk_label_set_text(data.instruction,instru);
           return;
         }
         if(check == ALLREADY)
         {
              sprintf(instru,"You have already tried it\nNote: You have have only %d guess left  to guess the word",NO); 
          gtk_label_set_text(data.instruction,instru);
           return;
         }
        
       /*for(i=0;i<4;i++)
         {     char win[10];    
                        if(Guessed_word[i]==Guesss_word[i])
                            
                    {   sprintf(win,"%c.png",Guessed_word[i]);
                   
                        gtk_image_set_from_file(data.l[i],win);
                    }
        } 
       */
            
         sprintf(str,"%d : %s COWS: %d BULLS: %d\n",GUESSES-NO,Guessed_word,COWS,BUFFS);
         sprintf(instru,"Enter your four letter guess word below and click Enter Guess\n.Note: You have have only %d guess left  to guess the word",NO);
         sprintf(cowaa,"Cows :%d",COWS);
         sprintf(bull,"Bulls :%d",BUFFS);
        const gchar *word=str;
        printf("%s",word);
        gtk_label_set_text(data.Cows,cowaa);
        gtk_label_set_text(data.Bulls,bull);
        gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(data.textbuffer),word,strlen(word)); 
        gtk_label_set_text(data.instruction,instru);
        if(NO==0)gtk_button_set_label(data.enterbutton,"Reveal Word"); 
        if(check == 1)
        {
            char win[4][10];
            int i;
            gtk_label_set_text(data.instruction,"You Win"); 
            NO=-10; 
            for(i=0;i<4;i++)
               {    sprintf(win[i],"%c.png",Guesss_word[i]);
                   
                    gtk_image_set_from_file(data.l[i],win[i]);
               }
           gtk_button_set_label(data.enterbutton,"Restart Game");
           gtk_widget_show(data.messagedialog1);
            
        }
        }
           else
           {   int i;
                char win[5][10];
               if(NO!=-10)
                   {
                              gtk_label_set_text(data.instruction,"You Lose");
                              for(i=0;i<4;i++)
                               {    sprintf(win[i],"%c.png",Guesss_word[i]);
                                   
                                    gtk_image_set_from_file(data.l[i],win[i]);
                               }
                           
                              gtk_button_set_label(data.enterbutton,"Restart Game");
                              gtk_widget_show(data.messagedialog2);
                    }
               }
     
    }
    
G_MODULE_EXPORT void
AboutWindow(GtkWidget* w,gpointer s)
{
    
    }

    
G_MODULE_EXPORT void
QUITAPP(GtkWidget* w,gpointer s)
{   gtk_widget_destroy(data.messagedialog1);
    gtk_widget_destroy(data.messagedialog2);
    
    gtk_widget_destroy(data.help);
gtk_widget_destroy(data.about);
gtk_widget_destroy(data.window);gtk_main_quit();

    
    }
   
    
int
main( int    argc,
      char **argv )
{
    GtkBuilder *builder;
    GtkWidget  *window;
    GtkCssProvider *Styler;
    GdkScreen *StartingScreen;
    gtk_init( &argc, &argv );
    Styler=gtk_css_provider_new();  
    
    /* Create builder and load interface */
    builder = gtk_builder_new();
    gtk_builder_add_from_file( builder,NAME_OR_PATH_OF_UI_FILE , NULL );
    gtk_css_provider_load_from_path (Styler,"style.css",NULL);
    StartingScreen=gdk_screen_get_default();
    gtk_style_context_add_provider_for_screen(StartingScreen,Styler,GTK_STYLE_PROVIDER_PRIORITY_USER);
    /* Obtain widgets that we need */
    data.window = GTK_WIDGET( gtk_builder_get_object( builder, "window1" ) );
    data.textbuffer=GTK_TEXT_BUFFER( gtk_builder_get_object( builder, "GussedWordList" ) );
    data.Filepath=GTK_ENTRY_BUFFER( gtk_builder_get_object( builder, "GuessWord" ) );
    data.DrawArea=GTK_DRAWING_AREA(gtk_builder_get_object( builder, "DrawArea" )) ;
    data.Cows=GTK_LABEL(gtk_builder_get_object( builder, "cows" ));
    data.Bulls=GTK_LABEL(gtk_builder_get_object( builder, "bulls" ));
    data.instruction=GTK_LABEL(gtk_builder_get_object( builder, "label1"));
    data.l[0]=GTK_IMAGE(gtk_builder_get_object( builder, "image1"));
    data.l[1]=GTK_IMAGE(gtk_builder_get_object( builder, "image4"));
    data.l[2]=GTK_IMAGE(gtk_builder_get_object( builder, "image5"));
    data.l[3]=GTK_IMAGE(gtk_builder_get_object( builder, "image6"));
    data.enterbutton=GTK_BUTTON(gtk_builder_get_object(builder, "button1"));
    data.help=GTK_WINDOW(gtk_builder_get_object(builder, "help"));
    data.about=GTK_WINDOW(gtk_builder_get_object(builder, "about"));
    data.messagedialog1=GTK_DIALOG(gtk_builder_get_object(builder, "messagedialog1"));
    data.messagedialog2=GTK_DIALOG(gtk_builder_get_object(builder, "messagedialog2"));
    gtk_widget_set_name(data.help,"HelpWindow");
    gtk_widget_set_name(data.about,"AboutWindow");

    /* Connect callbacks */
    load_word();
     
   gtk_builder_connect_signals( builder, &data );
    /* Destroy builder */
    g_object_unref( G_OBJECT( builder ) );
    /* Show main window and start main loop */
    gtk_widget_show( data.window );

   gtk_main();
 
 
    free(Styler);
    return( 0 );
}