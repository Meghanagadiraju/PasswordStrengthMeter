/*
University of San Francisco
CS221 - C and Systems Programming 
Instructor: Vahab Pournaghshband 
Author: Meghana Gadiraju
Due Date: October 17, 2018 
*/


#include <stdio.h>
#include <string.h>//strlen, strcmp, strcpy
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


//checks if user inputted password is strong
bool isStrongPassword(const char* username, const char* password) 
{
	
	//initializing username, password, and creating pointers for both
	int pw_len = strlen(password);
	int u_len = strlen(username);


	//initializing pointers in order to edit username and password
	const char *user_ptr = username;
	const char *pw_ptr = password;


	//declaring booleans to check conditions
 	bool up = false, low = false, dig= false, no_other = false, no_match = true, consecutive = false;

 	
	//checks conditions for lowercase character, uppercase character, integer character, and no other character (using ASCII values)
 	for (int i = 0; i < strlen(password); i++)
 	{

 		if ((int)password[i]>=65 && (int)password[i]<=90)//uppercase
 		{
 			up = true;
 		}
 		if ((int)password[i]>=97 && (int)password[i]<=122)//lowercase
 		{
 			low = true;
 		}
 		if ((int)password[i]>=48 && (int)password[i]<=57)//integer
 		{
 			dig = true;
 		}
 		if (((int)password[i]>=65 && (int)password[i]<=90)||((int)password[i]>=97 && (int)password[i]<=122)||((int)password[i]>=48 && (int)password[i]<=57))//no other
 		{
 			no_other = true;
 		}

 		

 	}


//checks conditions for 4 consecutive letter characters
 	int count = 0;
 	//itterates through array
 	for (int i = 0; i < pw_len; i++)
 	{
 		while (count < 4)
 		{	
	 		if (((int)password[i]>=65 && (int)password[i]<=90) || ((int)password[i]>=97 && (int)password[i]<=122))
			{
	 			count++;
	 			if (count == 3)
				{
	 				consecutive = true;
	 			}
	 		}
	 		else 
	 		{
	 			count = 0;
	 		}
	 	}	
 	}	

 		
	
	//checking to see if username is included in password
 	char lower_u [u_len];	//casting password and username to lowercase characters
 	char lower_pw [pw_len];
 	
  	for (int i = 0; i <u_len; i++)
  	{
  		lower_u[i] = tolower(username[i]);
  	}

  	for (int i = 0; i<pw_len; i++)
  	{
  		lower_pw[i] = tolower(password[i]);
  	}

  	//isinc = is included
 	char *isinc;
 	isinc = strstr (lower_pw, lower_u);

 	if (isinc != NULL)
 	{
 		no_match = false;
 	}

	//checking the overall strength of the password. 
 	if (pw_len >= 8 && up == true && low == true  && dig == true && no_other == true && no_match == true && consecutive == true)
 	{
 		//returning true for strong password
 		printf ("\nStrong Password!\n");
 		return true;
 	}
 	else
 	{
 		//returning false for weak password
 		printf("\nYour Password is Weak! Try Again.\n");
 		return false;
 	}
 	return false;

}


//This is the same as isStrongPassword, but does not include the consecutive letters part. 
bool isStrongDefaultPassword(const char* username, const char* password)
{

	//initializing username, password, and creating pointers for both
	int pw_len = strlen(password);
	int u_len = strlen(username);

	const char *user_ptr = username;
	const char *pw_ptr = password;


	//declaring booleans to check conditions
 	bool up = false, low = false, dig= false, no_other = false, no_match = true;

 	
	//checks conditions for lowercase character, uppercase character, integer character, and no other character (using ASCII values)
 	for (int i = 0; i < strlen(password); i++)
 	{

 		if ((int)password[i]>=65 && (int)password[i]<=90)//uppercase
 		{
 			up = true;
 		}
 		if ((int)password[i]>=97 && (int)password[i]<=122)//lowercase
 		{
 			low = true;
 		}
 		if ((int)password[i]>=48 && (int)password[i]<=57)//integer
 		{
 			dig = true;
 		}
 		if (((int)password[i]>=65 && (int)password[i]<=90)||((int)password[i]>=97 && (int)password[i]<=122)||((int)password[i]>=48 && (int)password[i]<=57))//no other
 		{
 			no_other = true;
 		}

 	}

	//checking to see if username is included in password
 	char lower_u [u_len];	//casting password and username to lowercaase characters
 	char lower_pw [pw_len];
 	
  	for (int i = 0; i <u_len; i++)
  	{
  		lower_u[i] = tolower(username[i]);
  	}
  	for (int i = 0; i<pw_len; i++)
  	{
  		lower_pw[i] = tolower(password[i]);
  	}

 	char *isinc;
 	isinc = strstr (lower_pw, lower_u);

 	if (isinc != NULL)
 	{
 		no_match = false;
 	}

	//checking the overall strength of the password. 
 	if (pw_len >= 8 && up == true && low == true  && dig == true && no_other == true && no_match == true)
 	{
 		//doesn't print anything because it is printed in generateDefaultPassword
 		return true;
 	}
 	else
 	{
 		return false;
 	}

}


char* generateDefaultPassword(char* default_password, const char* username)
{
	srand(time(0));//time
	
	int len_pw = (rand()%8)+8;//length of password will be at least 8 chars long and under 16 chars.
	char lower;
	char upper;
	int nums;

	bool strength = false;//strength initialized to false
	
	//generates passwords until a there is a strong password
	while (!strength)
	{
		for (int i = 0; i < len_pw; i++)//creating pw
		{

			int char_type = (rand()%3)+1;//assigns next char to be either a lowercase char, uppercase char, or an integer char
			if (char_type == 1)//lowercase letters
			{
				lower = (rand()%26)+97;
				default_password[i] = lower;
			}
			else if (char_type == 2)//uppercase letters
			{
				upper = (rand()%26)+65;
				default_password[i] = upper;
			}
			else if (char_type == 3)// numbers
			{
				nums = (rand()%10)+48;
				default_password[i] = nums;
			}

		}

		//checks if default password is strong
		if (isStrongDefaultPassword (username, default_password))
		{
			//prints strong generated password
			printf ("\nGenerating Default Password...\n");
			printf ("Generated Default Password: %s\n", default_password);
			strength = true;
		}

	}
	//returns strong default password
	return default_password;	
		

	

}

int main()
{	


	char myusername[30];
	char mypassword[30];
	char defpw [20];
	printf("Enter Username: ");
	scanf("%s", myusername);
	printf("\n");
	printf("Enter Password: ");
	scanf("%s", mypassword);
	isStrongPassword(myusername, mypassword);
	generateDefaultPassword(defpw, myusername);

	return 0;


}


