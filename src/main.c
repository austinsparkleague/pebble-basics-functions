
#include <pebble.h>
Window *my_window;
TextLayer *text_layer;
char output_string[800] = "";
int some_integer = 0;
bool do_increase = false;


//This is a quick overview of what a function is, particularly in the context of pebble development
//In simple terms, a function is a piece of code that you write to perform some action.  You then store
//that piece of code in memory just like a variable, and can then run that piece of code whenever you
//like, by "calling" or "invoking" that function. 
//These blocks of code make up all of the moving parts in a program, and they will come to be your good friends.

//If I failed to explain this stuff adequetly in the following example, 
//try reading this article=> http://www.tutorialspoint.com/cprogramming/c_functions.htm
//If that doesn't do it.  Don't worry, if you keep working on projects, one day it will just "click" for you.


//To define a custom function, we must first tell the compiler if this function will be returning any value.
//"returning" can be a tricky concept, but for now, just know that this function doesn't return anything, so
//we are going to put "void" in front of it.  Then we will write the name of the function.  In this case
//I have written a ridiculously long name, you don't have to do that, but I would encourage writing function
//names that allow you to tell what the function does generally without having to read every line of code in that function.
void custom_function_that_increases_some_integer_by_one(){
  
  //now we define what we want to happen inside this function.
  //here we are just increasing the value of some_integer by one.
  some_integer++;
}

//Great, that was fun.  Let's do another.  This function is going to return a value (hence the snappy name)
//and we are going to return an integer.  so we will communicate this
//to the program by putting "int" before the function instead of "void"
int custom_function_that_returns_a_value(){
  
  //now we define what we want to happen inside this function.
  //You'll be doing more useful things with your functions, 
  //like fetching tweets and returning the content of that tweet
  //or checking the weather forecast and returning the temperature,
  //but all this function does is spit a 12 back out.
  return 12;
}

//Now for the grand finale.  we are going to create a function that takes some input from another function
//and returns a value based on that input. 
//up til now we have been declaring all of our variables at the top of the document and they can then be
//used by any of our functions.  But sometimes you don't want to do that.  Sometimes you will find 
//that you want a variable that only the function you are in knows about.  
//this is also called a "local variable"
//but then what happens if you want to use that piece of information in a different function?
//the way we do that is to tell the function that we are going to pass a value to it inside parenthesis
//this is called a parameter.  You can name it anything you like, it doesn't have to have parameter in the name,
//by putting it in these parenthesis, you are using it like a place holder and you are letting the program know that
//when this function is called, we are going to give it a value to work with.
int custom_function_that_takes_a_parameter_and_returns_a_value(int parameter)
  {
  //now we want to do some awesome stuff with the value that has been passed in
  some_integer = (parameter * some_integer/2);
  
  //and return the result
  return some_integer;
  }

//not such a big deal, right?  At this point I'd recommend skipping to the bottom of this document where you see: START HERE! 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//WELCOME BACK <-----------------------------

//so now that you have seen that your program is actually just one function that calls three other functions. Let's see what's
//happening inside those functions.

//this is the definition of the "main_window_load" function. This is a custom function that we created
//Which is called by the initialize() function, which was itself called by the main() function.
//As I mentioned before, it is important that we define that function before it is used, so that is why it appears
//before the initialize() function which actually calls it below.
static void main_window_load(Window *window){

  //first, let's make a call to our custom function above.  Long name. Simple function.
  custom_function_that_increases_some_integer_by_one();
  
  //now let's try out a custom function that has a return value
  //we are going to assign the value of some_integer to be some_integer + whatever the return value of this
  //custom function is.
  some_integer += custom_function_that_returns_a_value(); 
  
  //up til now we have been declaring all of our variables at the top of the document and they can then be
  //used by any of our functions.  But sometimes you don't want to do that.  Sometimes you will find 
  //that you want a variable that only the function you are in knows about.  
  //this is also called a "local variable"
  int local_variable = 2;
  

  //in this case we have already defined up above that our function will be expecting one parameter,
  //and that parameter should be an integer.  So we are going to put "local_variable" in the parenthesis
  //and when we call this function it will run the code above and plug in the value for "local_variable"
  //into the function, where we have the word "parameter"
  some_integer += custom_function_that_takes_a_parameter_and_returns_a_value(local_variable);
  
  
  //Now we are going to use a built-in function that is defined "behind the scenes" in the code that we
  //imported when we wrote #include pebble.h
  //You won't see this function defined because it is added to the code from that pebble.h file that we
  //can't see in the cloud SDK that we are using right now.
  
  //snprintf() is a super handy function.  This will be one of your regulars, so get comfy.
  //this function takes four parameters which must appear in the expected order:
  //snprintf(a variable of type Char, the size of that variable, some text with % keys, some other variable that will be added to the text where there are %)
  //don't worry f this one doesn't make sense right away, just copy and paste for now.  Understanding will come.
  //for a full list of all of the %keys that you can use to add content to text read => http://developer.getpebble.com/docs/c/Standard_C/Format/#snprintf
  snprintf(output_string, sizeof(output_string), "the value of some_integer is: %i", some_integer);
  
  //here we use some other pre-defined functions to add a window layer and a text layer.
  Layer *window_layer = window_get_root_layer(window);
  text_layer = text_layer_create(GRect(0, 0, 144, 168));
  
  //finally we set our text to be the content of the output_string variable that we initialized at the top of the code
  //and then added data to by passing it into the snprintf() function.
  //this text_layer_set_text() function takes two parameters:
  //1)the layer that we would like to display text on, and 2)the text that we would like displayed on that layer.
  text_layer_set_text(text_layer, output_string );
  
  //we then have to add that text layer to the window layer so that the pebble knows where to display it.
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}



// here we have created the initial steps that we want to take place when this code is called from the "main" function
void initialize(void) {
  
  // this is another built-in function that returns a window layer variable.
  my_window = window_create();
  
  //now we add this window to the global window stack
  window_stack_push(my_window, true);
  
  //here we call the custom code above that changes the value of some_integer and adds text to a text layer.
  main_window_load(my_window);
  
}

// here we are defining the steps that we need our program to take when the user leaves our main window.
// notice that in the "main" function, the call to this code comes after the app_event_loop()
// In our case we are just cleaning house and releasing the memory that we allocated to create the window,
// but you could do anything you like here in addition to that.
void deinitialize(void) {
text_layer_destroy(text_layer);
window_destroy(my_window);
}


//START HERE!  <-------------------------------------
//here is the "main" function.  All C programs must have a main function.  This is the humble center of your program.
//all of the definitions for the different functions that are being called in main are given above.  This is because C
//requires that you define a function before it can be called.
//but it is this one main function that is called when you run your program.
//alright, now scroll back up to the "WELCOME BACK" section above.
int main(void) {
  initialize();
  app_event_loop();
  deinitialize();
}