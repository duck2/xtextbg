# drwr

drwr renders text with Xft and sets it as root background. so you can set `fortune`s or other stuff you like your background.

drwr is aware of `\n`. drwr is not aware of any other control characters. drwr will assume stdin is valid UTF-8.

### compiling

you need Xft and Xlib development libraries. `libxft-dev` and `libx11-dev` are the Debian packages.

if you are using something not Debian-ish, modify the `Makefile` so that it points to the X11 and Fontconfig libraries you use. you can also change the prefix to point to whatever unusual path you use.

modify `config.h` so `drwr` uses the font and color you want. then `make clean install`.


### using

`drwr x y`. it will `read()` from stdin which means you can enter only one line via the console.

`echo "fancy quote" | drwr 100 100`

or

```
cat > multiline_fancy_quote << EOF
...
drwr 100 100 < multiline_fancy_quote
```
