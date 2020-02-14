# Path-MTU

Path MTU is found by sending a data packet from source to destination. In the way, when the MTU of hops are less than the length of the packet, it returns the packet to the previous hop by mentioning the MTU value.
Once the MTU value is got by the hop which sent/forwarded the packet, fragments the string and resends it.
This process continues, until the packet reaches the destination.

###### Packet details: (struct packet_data)
- char string
- Source ID (integer)
- Destination ID (integer)
- length of the string
- MTU (intially while sender sends the packet, it is 0)

###### Table details: (struct table)- like a route table (Hardcoded)
- Source ID (integer)
- Destination ID (integer)
- Port to which the source ID and destination ID is binded.
	
#### Steps to execute the code:
- In packing the packet(), change the destination Id and source ID of your choice.(Advisable source and destination ID is 1/2/3) 
- Create different executable files while compiling it
- Enter the ID and port details, then the code prompts for choice 1. Sending the data 2. Hop (which may be the destination, known only when the packet reaches the hop and hop checks the destination ID equivalent to its ID)
- After getting the option, it prompts for them MTU
- The code gets executed, and packet reaches the destination and destination sends a success message to the sender.

#### Cases Supported:
- Three executables mode:
	- ID 1 sending data to ID 3 via ID 2
		- ID 3 having MTU lesser than ID 2 MTU
		- ID 3 having MTU equal or greater MTU than ID 2
		- ID 2 having MTU lesset than ID 3
	- Id 3 sending data to ID 1 via ID 2
		- ID 1 having MTU lesser than ID 2 MTU
		- ID 1 having MTU equal to greater than ID 2 MTU
		- ID 2 having MTU lesser than ID 1
	- ID 1 sending data to ID 2
	- ID 2 sending data to ID 1
	- ID 3 sending data to ID 2
	- ID 2 sending data to ID 3
	
#### Cases Not Supported:
- Four executable mode or More
	- ID 1 sending data to ID 4 via 2 hops ID 2 and ID 3
	- ID 4 sending data to ID 1 via 2 hops ID 3 and ID 2

	
