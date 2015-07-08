library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


entity Biestable_Det is
    Port ( async_reset : in  STD_LOGIC;
           ce : in  STD_LOGIC;
           clk : in  STD_LOGIC;
           d : in  STD_LOGIC;
           sync_reset : in  STD_LOGIC;
           q : out  STD_LOGIC);
end Biestable_Det;

architecture Behavioral of Biestable_Det is

begin

process (async_reset,ce,clk,d,sync_reset)
begin
   if async_reset ='1' then   
      q <= '0';
   elsif (clk'event and clk='1') then 
      if sync_reset = '1' then 
         q<= '0';
			elsif ce = '1'	then 	
			  q<=d;
      end if; 
   end if;
end process;

end Behavioral;
