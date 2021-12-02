#include <stdio.h>

/**
 * @brief Starting point function
 * 
 */

void app_main(void){
	
  /* Text File */
  extern const uint8_t indexHtml[] asm("_binary_index_html_start"); 
  extern const uint16_t indexHtmlLength asm("index_html_length");
  printf("HTML file size (from variable) = %d\n", indexHtmlLength);
  printf("HTML file = %s\n", indexHtml);

  printf("\n\n================\n\n");

  extern const uint8_t note[] asm("_binary_note_txt_start");
  extern const uint16_t noteTxtLength asm("note_txt_length");
  printf("Note file size (from variable) = %d\n", noteTxtLength);
  printf("Note file size = %s\n", note);

  printf("\n\n================\n\n");

  /* File */
  extern const uint8_t imageStart[] asm("_binary_polytech_png_start");  
  extern const uint8_t imageEnd[] asm("_binary_polytech_png_end"); 
  extern const uint16_t imageLength asm("polytech_png_length");
  const unsigned int imageSize = imageEnd - imageStart;
  printf("Image file size ((from variable)) = %d\n", imageLength);
  printf("Image file size = %d\n", imageSize);
  
  fflush(stdout);
}

