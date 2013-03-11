#include "resource.h"
#include "modules/client.h"
#include "modules/server.h"

int main()
{   
   Role role = CLIENT; // TODO: actually get role
 
   if (role == CLIENT)
      Client();
   else
      Server();

   return 0;
}