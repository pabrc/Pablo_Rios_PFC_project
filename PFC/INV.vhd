library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity inv is
    port(E : in std_logic;
         Q : out std_logic);
end inv;

architecture archi of inv is
 
begin
    
	 Q <= not E;
    
end archi;
