BASIC FatFS EXAMPLE -- using DataFlash as logical Disk
========================================================


** NOTE **:
LimiFrog must have been formatted as FAT file system first !
for example by plugging into Windows PC while USB firmware is running (if Flash is empty PC will offer to format disk)
or by running demo project "LimiFrog_FatFS-Format"
**********

Initialize Board
Launch USB so files can be checked from PC 

Open (create) a file FATFS.txt
Write a string in it
Close File

Open same file
Read String
Close file

Check that written and read back string have same length
Get LED to blink if success, else stay fixed



