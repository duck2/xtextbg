/* read this much from stdin */
#define MAX 1024

static char font[] = "Liberation Serif:size=32";
static XRenderColor color = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
static XRenderColor bgcolor = {0, 0, 0, 0xFFFF};

/* put (int) (line_spacing * font height) pixels between each line. */
static double line_spacing = 1.25;
