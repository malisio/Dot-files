#!/bin/bash 

passowrd="www.downloadly.ir"

wget -O ./AD_EXP/Ad_Pentest_part1_Downloadly.ir.rar "https://dl.downloadly.ir/Files/Elearning/Udemy_Active_Directory_Pentesting_Full_Course_-_Red_Team_Hacking_2021-4.part1_Downloadly.ir.rar?nocache=1725997391" 
wget -O ./AD_EXP/Ad_Pentest_part2_Dowloadly.ir.rar "https://dl.donloadly.ir/Files/Elearning/Udemy_Active_Directory_Pentesting_Full_Course_-_Red_Team_Hacking_2021-4.part2_Downloadly.ir.rar?nocache=1725997391"
wget -O ./AD_EXP/Ad_Pentest_part3_Dowloadly.ir.rar "https://dl.downloadly.ir/Files/Elearning/Udemy_Active_Directory_Pentesting_Full_Course_-_Red_Team_Hacking_2021-4.part3_Downloadly.ir.rar?nocache=1725997391"
wget -O ./AD_EXP/Ad_Pentest_part4_Dowloadly "https://dl.downloadly.ir/Files/Elearning/Udemy_Active_Directory_Pentesting_Full_Course_-_Red_Team_Hacking_2021-4.part4_Downloadly.ir.rar?nocache=1725997391"


echo $passowrd | unrar e  ./AD_EXP/Ad_Pentest_part1_Downloadly.ir.rar 
echo $passowrd | unrar e  ./AD_EXP/Ad_Pentest_part2_Downloadly.ir.rar 
echo $passowrd | unrar e  ./AD_EXP/Ad_Pentest_part3_Downloadly.ir.rar 
echo $passowrd | unrar e  ./AD_EXP/Ad_Pentest_part4_Downloadly.ir.rar 
