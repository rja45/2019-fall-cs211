# Design Diary
Use this space to talk about your process.  For inspiration, see [my prompts](../../../docs/sample_reflection.md) 4

10-SEP-19 to 20-SEP-19

My project is turning out signifcantly better than I expected. I have gotten further into the project than I imagined
at the start of the semester. I feel like all of my hard work and countless hours of research has really paid off.

After Milestone 1, I started messing around with getting my text showing on the screen in a consistent and scrollable way.
I first got a two-dimensional vector working to act as a buffer for the text, but the issue I ran into was controlling the 
cursor and having the cursor position represented within the vector during character inputs. I ended up not using the getyx()
and I made the cursor fully controlled by my own means rather than having pdcurses advance the cursor with input for me.
This simplified my program greatly(maybe if it could help me later on if I understand things better). Once I was able to 
get the cursor moving correctly and consistently inserting input characters into the vector in the desired locations,
I ran into issues with scrolling. 

Every time I would scroll, the text that went off of screen would disappear. After talking with Isaac and showing him my
code, he said that the value range of the buffer displaying on the screen doesn't look quite right. I analyzed that section
of code and found that he was absolutely right. I used debugging break points to figure out the correct values
to use for my buffer-screen printing. I ended up figuring out the relationship between the cursor, vectors, and the window
and got my scrolling and text input/output working consistently.  When I felt confident about my input/output, I started
tackling file loading.

For my file loading functionality, I ran into trouble getting the input into a string array for the ifstream functions.
I was running into issues with my understanding of how to recieve the text input to store it while also printing the
input to the screen for the user to see what they're typing. I ended up figuring out the string to char-array conversion
(as I'm sure my teacher demonstrated, but I didn't absorb). After this, I needed to figure out how to appropriately put the
characters being returned by the ifstream into the buffer/vector. I ended up figuring this out and got everything working 
according to the Milestone 2 objectives... or I thought. 

I didn't realize that I needed to have my program open WITH a file from the command line with a filename as an argument.
I followed the links in the Milestone 2.md file, I was a bit lost. I understood how the arguments got passed into
main by the arguments argc and argv, but I didn't understand where the .exe file was and I didn't understand how to actually
use the command line (powershell) with my program and the associated argument. Again, I met up with Isaac and he was able
to explain the way the project debugger "command line arguments" work within Visual Studio and the way the libraries and
.txt file need to be in the same folder as the .exe file. In class, my teacher's walkthough of command line project execution
really clarified things.

I did have to make an obviously inefficient choice to make my code work to meet Milestone 2; I initialized both dimensions 
of my two-dimensional vector/buffer to be far larger than the size of my screen/window to avoid certain issues based upon
my lack of understanding of vector functions requiring iterator(I think?). I will end up fixing this inefficiency later on
once I meet future objectives or I find the inefficiency preventing me from meeting objectives.

I have spent countless hours looking at countless articles/threads/videos to help me get through this project. Unfortunately
I have lost track of all of the links I have found and used. It has gotten to the point where I have been going through 
tens of links per hour and a small fraction of them actually proved to be useful for me. This is a great experience. I 
need to really work on making more commits even though my code may not be working or may not be the way I want it.
Messing around with my code without using git is proving to cause continual problems for me.

![Milestone2Demo](https://github.com/rja45/2019-fall-cs211/blob/master/projects/TextEditor/docs/Milestone02.gif)