#include "clientSettings.h"
#include "clientResetPassword.h"
#include "clientHome.h"
#include "clientDataStruct.h"
#include <stdio.h>

GtkWidget *Window;

//gets the settings of the user from the server and put it in the array
void getSettings(int userID, char *data[]);

void callHome(GtkWidget *widget, gpointer data){
	#ifdef DEBUG
	printf("Going to Home Page\n");
	gtk_main_quit();
	#endif	
	gtk_widget_destroy(Window);
	#ifndef DEBUG
        printHome(NULL, userIDGlobal);
	#endif
}

void callReset(GtkWidget *widget, gpointer data){
	#ifdef DEBUG
	printf("Going to ResetPW page\n");
	gtk_main_quit();
	#endif
        gtk_widget_destroy(Window);
	#ifndef DEBUG
        printResetPassword(NULL, NULL);
	#endif
}

void destroyWINDOW(GtkWidget *widget, gpointer data){
	Exit = 1;
	#ifdef DEBUG
	gtk_main_quit();	
	#endif
}

//1- call getSettings
//2- prints the gtk settings page

#ifndef DEBUG
void printSettings(GtkWidget *widget,  GtkWidget *list[]){
#endif

#ifdef DEBUG
int main(int argc, char *argv[]){
        gtk_init(&argc, &argv);
#endif

	GtkWidget *ChangePWButton,*HomeButton;
        GtkWidget *ChangePWLabel;
        GtkWidget *VSettingsBox, *HSettingsBox;
        GtkWidget *Title;
	GtkWidget *Home;
        GdkColor Color;
	GdkPixbuf *HomeBuff;

        Color.red = 0xFFFF;
        Color.green = 0x5353;
        Color.blue = 0x5353;

        Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_default_size(GTK_WINDOW(Window),400,500);
        gtk_window_set_position(GTK_WINDOW(Window),GTK_WIN_POS_CENTER);
        gtk_widget_modify_bg(Window, GTK_STATE_NORMAL, &Color);
        gtk_container_set_border_width(GTK_CONTAINER(Window), 90);
        gtk_window_set_resizable(GTK_WINDOW(Window), TRUE);

        Title = gtk_image_new_from_file("Icons/title.png");
	HomeBuff  = gdk_pixbuf_new_from_file_at_size("Icons/home.png", 50, 80, NULL);
	Home = gtk_image_new_from_pixbuf (HomeBuff);

        ChangePWButton = gtk_button_new_with_label("Edit");
        gtk_widget_set_size_request(ChangePWButton, 80, 80);
	HomeButton = gtk_button_new();
	gtk_button_set_image (GTK_BUTTON (HomeButton), Home);
	gtk_widget_set_size_request(HomeButton, 80, 80);
        ChangePWLabel = gtk_label_new("Password");


        VSettingsBox = gtk_vbox_new(0,30);

	HSettingsBox = gtk_hbox_new(0,100);

        gtk_box_pack_start(GTK_BOX(HSettingsBox), ChangePWLabel, 0, 0, 0);
        gtk_box_pack_start(GTK_BOX(HSettingsBox), ChangePWButton, 0, 0, 0);



        gtk_container_add(GTK_CONTAINER(Window), VSettingsBox);


        gtk_box_pack_start(GTK_BOX(VSettingsBox), Title, 0, 0, 0);
        gtk_box_pack_start(GTK_BOX(VSettingsBox), HSettingsBox, 0, 0, 0);
        gtk_box_pack_start(GTK_BOX(VSettingsBox), HomeButton, 0, 0, 0);

        g_signal_connect(ChangePWButton,"clicked", G_CALLBACK(callReset),NULL);
        g_signal_connect(Window,"delete-event",G_CALLBACK(destroyWINDOW),NULL);
	g_signal_connect(HomeButton,"clicked",G_CALLBACK(callHome),NULL);

        gtk_widget_show_all(Window);
	#ifdef DEBUG
	gtk_main();
	#endif
}

//returns a string to the font
char *getFont();

//returns an integer to the color
int getColor();

//checks if the password follow the naming conventions
//returns 1 if the password is valid, 0 otherwise
int getPassword(char *errorMessage);

//1- calls getFont
//2- update the font in the gtk page
//3- send the new font to the server
void updateFont(GtkWidget *widget,  GtkWidget *list[]);

//1- calls getColor
//2- update the color in the gtk page
//3- send the new font to the server
void updateColor(GtkWidget *widget,  GtkWidget *list[]);

//1- calls getPassword
//2- if valid ,update the password in the database
//3- print Password updated
void updatePassword(GtkWidget *widget,  GtkWidget *list[]);

