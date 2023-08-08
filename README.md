# Advanced-Unix-Shell-with-Pipelines-and-Command

This project comprises two interconnected C programs that create a unique Unix shell experience while incorporating a motivational quotes server. The first program, "unix_shell.c," implements an advanced Unix shell with pipelines and command assignment. Users can execute commands and establish pipelines between them using "|" and assign the output of one command as input to another using "=".

The second program, "quoteserver.c," acts as a server that serves motivational quotes to clients. It reads motivational quotes from a file, selects one randomly, and sends it to clients through named pipes. Clients request quotes by creating named pipes and sending their pipe names to the server.

When running the combined project, users are presented with a dynamic Unix shell environment that not only executes commands and handles pipelines but also displays random motivational quotes before each prompt. The integration of the motivational quotes server adds a unique and motivating touch to the traditional shell experience.

By combining these two programs, users can enhance their command-line interactions with the shell while receiving motivational quotes that provide an extra layer of inspiration. The seamless integration of these functionalities showcases advanced C programming concepts, including interprocess communication through named pipes and advanced file handling, making it an engaging and educational project for individuals looking to explore Unix systems programming.
