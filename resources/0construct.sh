#!/bin/bash

echo Processing Phoenixware Tiles
mono embedconv.exe -process pngtile -in phoenixware_tiles.png -out phoenixware_t.png -tile 8 8 -sprite 1 1
mono embedconv.exe -process pngbpp -in phoenixware_t.png -out phoenixware_tiles.bin -palette phoenixware.gpl -bpp 8
mono embedconv.exe -process bin2h -in phoenixware_tiles.bin -out phoenixware_tiles.h -cfile phoenixware_tiles.c -name phoenixware_tiles
rm phoenixware_t.png
rm phoenixware_tiles.bin

echo Processing Tiles
mono embedconv.exe -process pngtile -in luma_font.png -out luma_font_t.png -tile 8 8 -sprite 1 1
mono embedconv.exe -process pngbpp -in luma_font_t.png -out luma_font.bin -palette luma_font.gpl -bpp 8
mono embedconv.exe -process bin2h -in luma_font.bin -out luma_font.h -cfile luma_font.c -name luma_font
rm luma_font_t.png
rm luma_font.bin

echo Processing Tiles
mono embedconv.exe -process tmx2h -in phoenix.tmx -out phoenixware_logo.h
mono embedconv.exe -process tmx2h -in titlescreen2.tmx -out titlescreen.h
mono embedconv.exe -process tmx2h -in playarea.tmx -out playarea.h
mono embedconv.exe -process tmx2h -in completion.tmx -out completion.h
mono embedconv.exe -process tmx2h -in codeentry.tmx -out codeentry.h

# mono embedconv.exe -process bin2h -in music.sid -out music_sid.h -cfile music_sid.c -name music_sid
