#include <MultilineBoxLabel.h>

// MultilineBoxLabel functions #################################################
rcll_draw::MultilineBoxLabel::MultilineBoxLabel(){

}

rcll_draw::MultilineBoxLabel::~MultilineBoxLabel(){

}

void rcll_draw::MultilineBoxLabel::setLines(int lines){
    this->lines = lines;
}

void rcll_draw::MultilineBoxLabel::draw(cv::Mat &mat){
    if (backgroundcolor != rcll_draw::C_TRANSPARENT){
        // draw background rectangle
        cv::rectangle(mat, cv::Point(x, y), cv::Point(x + w, y + h), getColor(backgroundcolor), CV_FILLED, 8, 0);
    }

    if (bordercolor != rcll_draw::C_TRANSPARENT){
        // draw border rectangle
        cv::rectangle(mat, cv::Point(x, y), cv::Point(x + w, y + h), getColor(bordercolor), bordersize, 8, 0);
    }

    // split the text into lines
    std::vector<std::string> words = rcll_draw::splitString(content);
    std::vector<std::string> lines_str;
    lines_str.push_back("");
    for (size_t i = 0; i < words.size(); i++){
        int baseline = 0;
        std::string line = lines_str[lines_str.size() - 1] + " " + words[i];
        cv::Size textsize = cv::getTextSize(line, BASIC_FONT, fontsize, 2 * fontsize, &baseline);
        if (textsize.width < w){
            lines_str[lines_str.size() - 1] = line;
        } else {
            lines_str.push_back(" " + words[i]);
        }
    }

    // print the lines
    for (size_t i = 0; i < lines_str.size(); i++){
        if (lines_str[i] != ""){
            int baseline = 0;
            cv::Size textsize = cv::getTextSize(lines_str[i], BASIC_FONT, fontsize, 2 * fontsize, &baseline);
            cv::Point org = cv::Point(x, y + textsize.height + h*0.15 + i * (h*0.85)/lines);
            cv::putText(mat, lines_str[i], org, BASIC_FONT, fontsize, getColor(frontcolor), 2 * fontsize, 8, false);
        }
    }
}
