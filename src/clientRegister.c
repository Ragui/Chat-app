#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <gtk/gtk.h>
#include <netdb.h>
#include "clientRegister.h"
#include "clientDataStruct.h"

GtkWidget *lastNameLabel;
GtkWidget *firstNameLabel;
GtkWidget *userNameLabel;
GtkWidget *createPasswordLabel;
GtkWidget *emailAddressLabel;
GtkWidget *answerLabel;
GtkWidget *registerMessageLabel;
GtkWidget *box;
GtkWidget *chatBotLogo;

GtkWidget *firstNameEntry;
GtkWidget *lastNameEntry;
GtkWidget *usernameEntry;
GtkWidget *passwordEntry;
GtkWidget *emailEntry;

GtkWidget *firstNameBox;
GtkWidget *lastNameBox;
GtkWidget *userNameBox;
GtkWidget *createPasswordBox;
GtkWidget *emailBox;
GtkWidget *combo_box;
GtkWidget *answerBox;

GtkWidget *window;
GtkWidget *submitButton;
GtkWidget *box1, *box2;
GtkWidget *label, *aLabel;
GtkWidget *submitBox;
GtkWidget *questionBox;
GtkWidget *questionLabel;

PangoFontDescription *df;

void destroyW(GtkWidget *widget, gpointer data)
{
	Exit = 1;	
}

GdkColor getTemplateColor(GdkColor color)
{

        color.red = 0xFFFF;
        color.green = 0x5353;
        color.blue = 0x5353;

        return color;
}

/*void printRegister(GtkWidget *widget, GtkWidget *list[])
{
        const gchar *entry_text;
        entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
        gtk_entry_set_text(GTK_ENTRY(entry), "");
        printf("Entry contents: %s\n", entry_text);
}
*/
//prints the gtk register pagei
void printRegister(GtkWidget *widget,  GtkWidget *list[])
{
	extern registration data2;	

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        initialize_window(window);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
        gtk_window_set_default_size(GTK_WINDOW(window),400,500); 
        box1 = gtk_vbox_new(FALSE, 20);

	firstNameBox 	  = gtk_hbox_new(TRUE, 10);
	lastNameBox 	  = gtk_hbox_new(TRUE, 10);
	userNameBox 	  = gtk_hbox_new(TRUE, 10);
	createPasswordBox = gtk_hbox_new(TRUE, 10);
	emailBox   = gtk_hbox_new(TRUE, 10);
	questionBox = gtk_hbox_new(TRUE, 10);
	answerBox = gtk_hbox_new(TRUE, 10);
	
	chatBotLogo = gtk_image_new_from_file("Icons/title.png");	
        gtk_box_pack_start(GTK_BOX(box1), chatBotLogo, FALSE, FALSE, 0);
        gtk_widget_show(chatBotLogo);

        aLabel = gtk_label_new("Welcome to ChatBot \n   Account Set Up");
        df = pango_font_description_from_string("Monospace");
        pango_font_description_set_size(df,PAGE_DESC_SIZE*PANGO_SCALE);
        gtk_widget_modify_font(aLabel, df);

        gtk_misc_set_alignment(GTK_MISC(aLabel), 0.5, 0);
        gtk_box_pack_start(GTK_BOX (box1), aLabel, FALSE, FALSE, 0);
        gtk_widget_show(aLabel);

	data2.fName 	= gtk_entry_new();
	data2.lName 	= gtk_entry_new();
	data2.email 	= gtk_entry_new();
	data2.userName	= gtk_entry_new();
	data2.password 	= gtk_entry_new();
	data2.answer 	= gtk_entry_new();

	firstNameLabel 		= gtk_label_new("First Name:");
	lastNameLabel 		= gtk_label_new("Last Name:");
	userNameLabel 		= gtk_label_new("Enter Username:");
	emailAddressLabel	= gtk_label_new("Enter Email:"); 
	createPasswordLabel 	= gtk_label_new("Create Password:");
	questionLabel 		= gtk_label_new("Security Question:");
	answerLabel		= gtk_label_new("Answer:");
	registerMessageLabel	= gtk_label_new(NULL);

// label = gtk_label_new(charString);
        gtk_misc_set_alignment(GTK_MISC(firstNameLabel), 1, 0);
        gtk_misc_set_alignment(GTK_MISC(lastNameLabel), 1, 0);
        gtk_misc_set_alignment(GTK_MISC(userNameLabel), 1, 0);
        gtk_misc_set_alignment(GTK_MISC(emailAddressLabel), 1, 0);
        gtk_misc_set_alignment(GTK_MISC(createPasswordLabel), 1, 0);
	gtk_misc_set_alignment(GTK_MISC(questionLabel), 1, 0);
	gtk_misc_set_alignment(GTK_MISC(registerMessageLabel), 0.5, 0);
	gtk_misc_set_alignment(GTK_MISC(answerLabel), 1, 0);
		
	gtk_box_pack_start(GTK_BOX(firstNameBox), firstNameLabel, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(lastNameBox), lastNameLabel, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(userNameBox), userNameLabel, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(emailBox), emailAddressLabel, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(createPasswordBox), createPasswordLabel, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(questionBox), questionLabel, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(answerBox), answerLabel, FALSE, FALSE, 0);
		
	gtk_widget_show(firstNameLabel);
	gtk_widget_show(lastNameLabel);
	gtk_widget_show(userNameLabel);
	gtk_widget_show(emailAddressLabel);
	gtk_widget_show(createPasswordLabel);
	gtk_widget_show(answerLabel);
	gtk_widget_show(registerMessageLabel);

        gtk_entry_set_max_length(GTK_ENTRY(data2.fName), 26);
        gtk_entry_set_max_length(GTK_ENTRY(data2.lName), 26);
        gtk_entry_set_max_length(GTK_ENTRY(data2.userName), 26);
        gtk_entry_set_max_length(GTK_ENTRY(data2.email), 26);
        gtk_entry_set_max_length(GTK_ENTRY(data2.password), 26);
	gtk_entry_set_visibility(GTK_ENTRY(data2.password), FALSE);
	gtk_entry_set_max_length(GTK_ENTRY(data2.answer), 26);
       
	gtk_entry_set_invisible_char(GTK_ENTRY(data2.password), '*');
	
	gtk_box_pack_start(GTK_BOX(firstNameBox), data2.fName, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(lastNameBox), data2.lName, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(userNameBox), data2.userName, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(emailBox), data2.email, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(createPasswordBox), data2.password, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(answerBox), data2.answer, FALSE, FALSE, 0);


	data2.question = gtk_combo_box_new_text();
        gtk_combo_box_append_text(GTK_COMBO_BOX(data2.question),"Where were you born?");
        gtk_combo_box_append_text(GTK_COMBO_BOX(data2.question),"What is your first car?");
        gtk_combo_box_append_text(GTK_COMBO_BOX(data2.question),"What is your favorite animal?");
        gtk_combo_box_append_text(GTK_COMBO_BOX(data2.question),"What is your favorite musician?");
        gtk_combo_box_append_text(GTK_COMBO_BOX(data2.question),"What is your favorite color?");

	gtk_box_pack_start(GTK_BOX(questionBox), data2.question, FALSE, FALSE, 0);

		
	gtk_widget_show(data2.fName);
	gtk_widget_show(data2.lName);
	gtk_widget_show(data2.userName);
	gtk_widget_show(data2.email);
	gtk_widget_show(data2.password);
	gtk_widget_show(data2.answer);


	gtk_widget_show(firstNameBox);
	gtk_widget_show(lastNameBox);
	gtk_widget_show(userNameBox);
	gtk_widget_show(emailBox);
	gtk_widget_show(createPasswordBox);
	gtk_widget_show(answerBox);
	gtk_widget_show(questionBox);
	gtk_widget_show(data2.question);

	gtk_box_pack_start(GTK_BOX (box1), firstNameBox, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX (box1), lastNameBox, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX (box1), userNameBox, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX (box1), emailBox, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX (box1), createPasswordBox, FALSE, FALSE, 0);
	 gtk_box_pack_start(GTK_BOX (box1), questionBox, FALSE, FALSE, 0);
	 gtk_box_pack_start(GTK_BOX (box1), answerBox, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX (box1), registerMessageLabel, FALSE, FALSE, 0);

        submitBox = gtk_hbox_new(FALSE, 0);
        submitButton = gtk_button_new_with_label("Submit");
        gtk_box_pack_start(GTK_BOX (submitBox), submitButton, TRUE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX (box1), submitBox, FALSE, FALSE, 0);

        gtk_container_add(GTK_CONTAINER (window), box1);
       

	gtk_widget_show(submitButton);
        gtk_widget_show(submitBox);
        gtk_widget_show(box1);
        gtk_widget_show (window);
	gtk_widget_show_all(window);

	
	g_signal_connect(submitButton, "clicked", G_CALLBACK(getRegisterData), 
			 &data2);
        g_signal_connect (window, "delete_event",
                            G_CALLBACK(destroyW), NULL);
	
	gtk_widget_show(submitButton);
        gtk_widget_show(submitBox);
        gtk_widget_show(box1);
        gtk_widget_show (window);
	gtk_widget_show_all(window);
}

#ifdef DEBUG
int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	printRegister(NULL, NULL);
	g_signal_connect(submitButton, "clicked", G_CALLBACK(getRegisterData), &data);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_main();
	
	return 0;
}
#endif

//1- get the input data when the register button is clicked
//2- call validateRegisterData
//3- a- if valid, call printHome
//   b- if not, add an error message to the old registerPage
void getRegisterData(GtkWidget *widget, registration *data)
{
	const char *fName;
	const char *lName;
	const char *uName;
	const char *email;
	const char *password;
	const char *answer;
	int question;
	int userID = -1;
	
	fName	 = gtk_entry_get_text(GTK_ENTRY(data->fName));
	lName 	 = gtk_entry_get_text(GTK_ENTRY(data->lName));
	uName 	 = gtk_entry_get_text(GTK_ENTRY(data->userName));
	email 	 = gtk_entry_get_text(GTK_ENTRY(data->email));
	password = gtk_entry_get_text(GTK_ENTRY(data->password));
	answer = gtk_entry_get_text(GTK_ENTRY(data->answer));
	question = gtk_combo_box_get_active(GTK_COMBO_BOX(data->question));	

	if(!*fName)
	{
		gtk_label_set_text(GTK_LABEL(registerMessageLabel), "Please enter your first name.");
	}
	else if(!*lName)
	{	
		gtk_label_set_text(GTK_LABEL(registerMessageLabel), "Please enter your lat name.");
	}
	else if(!*uName)
	{
		gtk_label_set_text(GTK_LABEL(registerMessageLabel), "Please provide a username\n (no spaces)");
	}
	else if(!*email)
	{
		gtk_label_set_text(GTK_LABEL(registerMessageLabel), "Please provide a valid email");
	}
	else if(!*password)
	{
		gtk_label_set_text(GTK_LABEL(registerMessageLabel), "Please create a password.\n (no spaces)");
	}
	else if(question == -1)
        {
                gtk_label_set_text(GTK_LABEL(registerMessageLabel), "Please choose a question.\n (no spaces)");
	}
	else if(!*answer)
        {
                gtk_label_set_text(GTK_LABEL(registerMessageLabel), "Please provide an answer.\n (no spaces)");
	}
//	else
//	{
//		gtk_label_set_text(GTK_LABEL(registerMessageLabel), "You already have an account!");
//	}


	
	if(strlen(fName) < 2)
	{
		
		gtk_label_set_text(GTK_LABEL(registerMessageLabel), "first name is too short,\nshouuld be at least 2 characters");
		return;
	}

	if(strlen(lName) < 2)
	{
			
		gtk_label_set_text(GTK_LABEL(registerMessageLabel), "last name is too short, \nshould be at least 2 characters");
	 	return;
	}
	if(strlen(uName) < 6)
	{
		
		gtk_label_set_text(GTK_LABEL(registerMessageLabel), "username is too short,\nshould be more than 6 characters");
		return;
	}

	if(strlen(email) < 6)
	{
			
		gtk_label_set_text(GTK_LABEL(registerMessageLabel), "email must include @emaildomain.com");
		return;
	}
	
	if(strlen(password) < 6)
	{
		
		gtk_label_set_text(GTK_LABEL(registerMessageLabel), "Password is too short, \n should be at least 6 characters");
		return; 
	}

	
	#ifdef DEBUG
		printf("First name  is: %s\nLast name is: %s\nUsername is: %s\nEmail Address is: %s\nPassword is: %s\n ", fName, lName, uName, email, password);

	#endif

// question about passing the *data to validateRegisterData	
	userID = validateRegisterData(fName, lName, uName, email, password, question, answer);
	
	#ifdef DEBUG
	printf("User ID is %d\n", userID);
	#endif
	
	if(userID != -1)
	{	
		usernameGlobal = malloc(sizeof(char) *strlen(uName) + 1);
		strncpy(usernameGlobal, uName, strlen(uName));
		gtk_widget_destroy(window);
		printHome(NULL, userID);
	}
	else{
		gtk_label_set_text(GTK_LABEL(registerMessageLabel), "Username already found!");
	}
	userIDGlobal = userID;
}

int validateRegisterData(const char *fName, const char *lName, 
			 const char *uName, const char *email,
			 const char *password, const int question, const char *answer)
{
	int userID = -1;	// id value set to arbibary value for right now in order to test the window terminates
	char errorMessage[256];
	memset(errorMessage, 0, sizeof(errorMessage));
	
	char regBuff[256];	// assuming the sum of all the characters is less than 500
	memset(regBuff, 0, sizeof(regBuff));			//allocation of memory for string buffer
	/*strncpy(regBuff, "REGISTER ", strlen("REGISTER "));	//adds the word register to string buffer
	strncat(regBuff, fName, strlen(fName));		//adds username to strin butter
	strncat(regBuff, " ", 1);				//this is probs used for spacing to read next text
	strncat(regBuff, lName, strlen(lName));		//adds username to strin butter
	strncat(regBuff, " ", 1);				//this is probs used for spacing to read next text
	strncat(regBuff, uName, strlen(uName));		//adds username to strin butter
	strncat(regBuff, " ", 1);				//this is probs used for spacing to read next text
	strncat(regBuff, email, strlen(email));		//adds username to strin butter
	strncat(regBuff, " ", 1);				//this is probs used for spacing to read next text
	strncat(regBuff, password, strlen(password));		
	strncat(regBuff, " ", 1);*/				//this is probs used for spacing to read next text

	sprintf(regBuff, "REGISTER %s %s %s %s %s %d %s", fName, lName, uName, email, password, question+1, answer);

	printf("Exit: %d\nThe user buffer: %s\n", Exit, regBuff);

	#ifndef DEBUG
	// creating, and opening a socket to connect to server
	extern int socketFD;
	extern struct sockaddr_in serverAddress;
	socketFD = socket(AF_INET, SOCK_STREAM, 0);
	if(socketFD < 0)
	{
		error("Error opening socket");
	}

	if(connect(socketFD, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0)
	{
		
		error("connecting to server failed");
	}

	int u, s;
	u = write(socketFD, regBuff, strlen(regBuff));
	if(u < 0)
	{
		error("Error writing to the server.\n");
	}
	
	printf("message sent\n");
	s = read (socketFD, errorMessage, sizeof(errorMessage) -1);
	if(s < 0)
	{
		error("Error reading from server");
	}	
	errorMessage[s] = 0;
	#endif
	printf("Response: '%s'\n", errorMessage);
	

	if(strncmp("REGISTER OK", errorMessage, strlen("REGISTER OK")) ==  0)
	{
		sscanf(errorMessage,"%*s %*s %d", &userID);
	}
	else if(strncmp("Unable to complete registration", errorMessage, strlen("Unable to complete registration") == 0))
	{
		gtk_label_set_text(GTK_LABEL(registerMessageLabel), "Username already found!");
	}
	return userID;
}	


void initialize_window(GtkWidget *window)
{
        GdkColor color;
        color = getTemplateColor(color);
        gtk_window_set_title(GTK_WINDOW(window), "Client Registration");
        gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
        gtk_container_set_border_width(GTK_CONTAINER(window), WINDOW_BORDER);
        gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color);
}
