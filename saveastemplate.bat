@ECHO off
COLOR F0
ROBOCOPY .\ %AppData%\CodeBlocks\UserTemplates\SFML_B~1\ /MIR /IS /R:1 /XD bin obj .git