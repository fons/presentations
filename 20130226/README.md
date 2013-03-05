# [New York City C++ Meetup Feb 26 2013](http://www.meetup.com/nyccpp/events/96847082/)

## Presentation

I present a broad overview of functional programming in c++. The presentation is in pdf, keynot and poer point format.

In addition to the presentation, you'll also find the source code of the examples here.
Just clone the repo and run make. I used the mac ports version of gcc 4.7. The examples do rely on features in c++11, so older compilers may not work.

*make* will produce a an executable called main. when you run main, a prompt (->) should appear. You can enter ? and it will display a list of commands.
You can choose one of the examples in the presentation, and the resulst will be displayed at the prompt. The '**' terminates what's displayed.

Here's a sample session :

newt:func fons$ ./main 
>-> ?
>-> bind_1,bind_4,functor_1,functor_3,lambda_1,
>-> lambda_6,lambda_7,lambda_8,lambda_9,m_1,
>-> m_2,trans_1,trans_2,trans_3,trans_4,
>-> trans_5,trans_6,
>-> h  : history
>-> !  : last command
>-> !n : command at position n
>-> m_1
>-> executing m_1
>results : 
>27
>91
>157
>47
>-11
>3
>     ***     
>-> 