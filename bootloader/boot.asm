org 0x7c00 ; Loading the 512-byte Code to 0000:7c00
mov ax,cs
mov ds,ax
mov es,ax
call DisplayStr ; Call the Follow Routine to Display Strings
call DisplayErr
call DisplayErr
call DisplayErr
jmp $ ; Infinite Loop
DisplayStr:
mov ax, BootMessage
mov bp, ax
mov cx, 93 ; Length of String
mov ax, 0x1301
mov bx, 0x000f ; Forecolor=Red/BackgroundColor=Black
mov dl,0
int 0x10
ret
DisplayErr:
mov ax, ErrorMessage
mov bp, ax
mov cx, 81 ; Length of String
mov ax, 01301h
mov bx, 000ch ; Forecolor=Red/BackgroundColor=Black
mov dh,4
int 10h
ret
BootMessage:db 'Gakiton OS v0.0.1.0001',13,10,'Copyright 2018 Tenton Lien. All Rights Reserved.',13,10,13,10,'Loading Kernel...'
ErrorMessage:db '[ERROR] Kernel Not Found.',13,10,'[ERROR] Kernel Not Found.',13,10,'[ERROR] Kernel Not Found.',13,10
mov ah,02h
mov dl,0dh
int 21h
mov ah,02h
mov dl,0ah
int 21h
times 510- ($-$$) db 0 ; Fill the Rest of Blank Position 
dw 0xaa55 ; Sign of End