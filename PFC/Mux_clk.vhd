library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


entity Mux_clk is
    Port ( async_reset : in  STD_LOGIC;
           en : in  STD_LOGIC;
			  in0,in1,in2,in3,in4 : in  STD_LOGIC;
           sel : in  STD_LOGIC_VECTOR (2 downto 0);
           sync_reset : in  STD_LOGIC;
           q : out  STD_LOGIC );
end Mux_clk;

architecture Behavioral of Mux_clk is

begin

process (async_reset,en,sel,sync_reset,in0,in1,in2,in3,in4)
begin
   if async_reset ='1' then   
      q <= '0';
   elsif   sync_reset = '1' then 
         q<= '0';
	elsif en = '1'	then 
	
		CASE sel IS
		
    WHEN  "000"  =>  q <= in0;
    WHEN  "001"  =>  q <= in1;
    WHEN  "010"  =>  q <= in2;
    WHEN  "011"  =>  q <= in3;
	 WHEN  "100"  =>  q <= in4;
    WHEN OTHERS =>   q  <= '0';
  END CASE;
  else q<='0';
   end if;
end process;

end Behavioral;