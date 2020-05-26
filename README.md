# Path-MTU

Path MTU is found by sending a data packet from source to destination. In the way, when the MTU of hops are less than the length of the packet, it returns the packet to the previous hop by mentioning the MTU value.
Once the MTU value is got by the hop which sent/forwarded the packet, fragments the string and resends it.
This process continues, until the packet reaches the destination.

###### Packet details: (struct packet_data)
- <div style="color: blue">char string
- Source ID (integer)
- Destination ID (integer)
- length of the string
- MTU (intially while sender sends the packet, it is 0)
</div>

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
	- Node 1 sending data to Node 3 via Node 2
		- Node 3 having MTU lesser than Node 2 MTU
		- Node 3 having MTU equal or greater MTU than Node 2
		- Node 2 having MTU lesset than Node 3
	- Node 3 sending data to Node 1 via Node 2
		- Node 1 having MTU lesser than Node 2 MTU
		- Node 1 having MTU equal to greater than Node 2 MTU
		- Node 2 having MTU lesser than Node 1
	- Node 1 sending data to Node 2
	- Node 2 sending data to Node 1
	- Node 3 sending data to Node 2
	- Node 2 sending data to Node 3
	
#### Cases Not Supported:
- Four executable mode or More
	- Node 1 sending data to Node 4 via 2 hops Node 2 and Node 3
	- Node 4 sending data to Node 1 via 2 hops Node 3 and Node 2

	
