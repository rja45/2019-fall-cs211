# Design Diary
Use this space to talk about your process.  For inspiration, see [my prompts](../../../docs/sample_reflection.md) ]

August 27, 2019 – September 9, 2019

		I started my project without having used C++, Visual Studio, and GitHub before. 
	My first task was to get a handle on the C++ language. I found a YouTube tutorial
	series and followed the tutorials closely the entire way through. The tutorial series
	was about 9 hours long, but I spent much more time than that due to re-watching 
	many of the tutorials. I realized that C++ is pretty similar to Java, which I am 
	more familiar with.

		After I felt I had a good basic understanding of C++, I decided to dive into C++
	programming by building upon the Text Editor that was made during Lab 1. I quickly ran 
	into issues when I attempted to run the curses Examples. I ended up getting side-tracked
	trying to figure out why my Examples wouldn’t work. I realized that my issues with the
	Examples were due to my lack of understanding about Header files and Libraries. I ended
	up watching several more YouTube videos related to C++, Visual Studio, Header files, C++
	Linker, Static Libraries, and Dynamic Libraries.

	Although I spent a lot of time researching how to fix my problem, I could not actually fix
	my problem with what I had learned. After speaking with my Professor and having him build
	an Example for me, the Examples started working properly. It was determined that I altered 
	the files related to the Examples which broke my linking (as far as I understand the issue.)

	   I was able to make some productive changes to my Text Editor program. I added some color 
	and prompt features, added some exit and save prompts which both have confirm prompts, and
	made the general appearance of the Text Editor what I would like it to look like for the 
	time being.

	   After I was able to get my Text Editor functioning with my appearance changes, I found that 
	I was unable to deal with “CTRL+S” type of key inputs. I wanted to make my “menu” options 
	accessible through these ctrl+button functions, but I could not figure it out. I ended up 
	changing the structure of my menu options to check for function key inputs. Once I was able
	to check for key input related to menu options, I wanted to tackle the issue of window resizing.
	I was able to figure that out, but only partially. I was able to detect for terminal resizing
	events, but I was unable to adequately redraw/refresh the window while having it maintain its 
	visual integrity. To resolve this, I will be looking into the example resizing code that was 
	posted to the class repository.

		I ran into issues understanding git and GitHub, but I scheduled office hours with the
	professor to figure these issues out. Hopefully I won't be having any more git/GitHub-related 
	issues, but at this point I feel like I'm ready for anything.
	
		My next objective is to make my text output to the screen properly and word wrap correctly
	without disturbing the colored border surrounding the Text Editor. I am not exactly sure how I
	will accomplish this, but a chat with a fellow classmate, Jordan, opened my mind to the idea
	of using a buffer. After I complete the objectives above, I would like to ensure that the 
	word-wrap works properly with resizing and I’ll work on a way to enable vertical scrolling
	within the Text Editor. At some point I will need to make the load/save functionality of the
	program, but I will need to figure out some of the other objectives beforehand.

		I’m sure I will be finding many other hurdles/objectives in coming days. I will be sure to make 
	notes about my progress. I have spent at least 50 hours doing research and completing objectives 
	related to this project so far (I have lost track of the URL links to the dozens of resources 
	I’ve been digging through). This project has taken a large majority of the time I spend studying
	this semester, but I am glad I’m studying so hard. I’m hoping I’ll be able to have more significant
	improvements to my Text Editor project in the coming weeks so I can actually demonstrate what 
	I’ve been learning. 
