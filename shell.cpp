#include <Shell.h>
#include <AceRoutine.h>
#include "navigation.h"

using namespace ace_routine;

class Shell_printer : public Print
{
public:
  virtual size_t write(uint8_t);
};
size_t Shell_printer::write(uint8_t character) { shell_putc(character); }
Shell_printer shell_printer;

int shell_reader(char * data)
{
  // Wrapper for Serial.read() method
  if (Serial.available()) {
    *data = Serial.read();
    return 1;
  }
  return 0;
}

void shell_writer(char data)
{
  // Wrapper for Serial.write() method
  Serial.write(data);
}

int command_tasks(int argc, char** argv)
{
  shell_println("Coroutines");
  shell_println("");
  CoroutineScheduler::list(shell_printer);

  return SHELL_RET_SUCCESS;
}

int command_navigate(int argc, char** argv)
{
  shell_println("Navigation");
  shell_println("");

  // Parse args
  for(int i = 0; i < argc; i++)
  {
      String arg = argv[i];
      if(arg == "-d" || arg == "--dest" && i < argc - 1)
      {
          navigate_to(atoi(argv[i+1]));
      }
      if(arg == "-c" || arg == "--current" && i < argc - 1)
      {
          set_current_tag(atoi(argv[i+1]));
      }
      if(arg == "-l" || arg == "--link" && i < argc - 2)
      {
          int tag1 = atoi(argv[i+1]);
          int tag2 = atoi(argv[i+2]);

          link_tags(tag1, tag2);
      }
      if(arg == "-h" || arg == "--help" || arg == "help")
      {
          shell_println("Command line options:");
          shell_println("-d  --dest       Set the destination tag ID");
          shell_println("-c  --current    Set the current tag ID");
          shell_println("-l  --link       Link two tags by ID. Takes two tag IDs");
          shell_println("-h  --help       Helo");
      }
  }

  shell_printf("Current tag: %d\r\n", get_current_tag());
  shell_printf("Destination tag: %d\r\n", get_destination_tag());
  shell_printf("Next tag: %d\r\n", next_tag());

  return SHELL_RET_SUCCESS;
}

void shell_setup()
{
  shell_init(shell_reader, shell_writer, 0);
  shell_register(shell_print_commands, PSTR("help"));
  shell_register(command_tasks, PSTR("tasks"));
  shell_register(command_navigate, PSTR("nav"));
}

COROUTINE(shell)
{
  COROUTINE_BEGIN();

  shell_setup();

  while (true)
  {
    shell_task();
    COROUTINE_YIELD();
  }
  
  COROUTINE_END();
}