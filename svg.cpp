#include "svg.h"
void
svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}
void
svg_end()
{
    cout << "</svg>\n";
}
void
svg_rect(double x, double y, double width, double height,string stroke, string fill)
{
    cout << "<rect x='"<<x<<"' y='"<<y<<"' width='"<<width<<"' height='"<<height<<"' stroke='"<<stroke<<"' fill='"<<fill<<"' />";
}
void
svg_text(double left, double baseline, string text,size_t bin)
{
    cout << "<text x='"<<left<<"' y='"<<baseline<<"'>"<<bin<<"</text>";
}
string
color_choice (size_t color, size_t max_count, size_t bin)
{
string shade;
if(bin==0)
shade="#999";
else
shade='#'+ to_string(color*(size_t)(10-(bin * 9.0)/max_count));
return shade;
}
void
show_histogram_svg(const vector<size_t>& bins)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const auto COLOR = 111;
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;
    string fillcolor;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    size_t max_count = 0;
    for (size_t count : bins)
    {
        if (count > max_count)
        {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;
    double scaling_factor = 1;
    for (size_t bin : bins)
    {
        fillcolor=color_choice(COLOR,max_count,bin);
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin),bin);
        if (scaling_needed)
        {
            scaling_factor = (double)MAX_ASTERISK / max_count;
            bin = (size_t)(bin * scaling_factor);
        }
        const double bin_width = BLOCK_WIDTH * bin;
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,"black",fillcolor);
        top += BIN_HEIGHT;
    }
    svg_end();
}
