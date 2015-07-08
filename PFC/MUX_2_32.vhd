library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


entity Mux2_32 is
    Port ( async_reset : in  STD_LOGIC;
           a : in  STD_LOGIC_VECTOR (31 downto 0);
           b : in  STD_LOGIC_VECTOR (31 downto 0);
			  sel : in  STD_LOGIC;
           q : out  STD_LOGIC_VECTOR (31 downto 0));
end Mux2_32;

architecture Behavioral of Mux2_32 is

begin

process (async_reset,a,b,sel)
begin

   if async_reset ='1' then   
      q <= x"00000000";
   else
	
		CASE sel IS
			WHEN  '0'  =>  q <= a;
			WHEN  '1' =>  q <= b;
			WHEN OTHERS =>   q  <= x"00000000";
		END CASE;
		
   end if;
	
end process;

end Behavioral;