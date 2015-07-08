library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


entity Mux2 is
    Port ( async_reset : in  STD_LOGIC;
           a : in  STD_LOGIC;
           b : in  STD_LOGIC;
			  sel : in  STD_LOGIC;
           q : out  STD_LOGIC);
end Mux2;

architecture Behavioral of Mux2 is

begin

process (async_reset,a,b,sel)
begin
   if async_reset ='1' then   
      q <= '0';
   
     else
	
		CASE sel IS
		
    WHEN  '0'  =>  q <= a;
    WHEN  '1' =>  q <= b;
    WHEN OTHERS =>   q  <= '0';
  END CASE;
   end if;
end process;

end Behavioral;