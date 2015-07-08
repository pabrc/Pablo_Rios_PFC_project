library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


entity Biestable_D is
    Port ( async_reset : in  STD_LOGIC;
           en : in  STD_LOGIC;
           clk : in  STD_LOGIC;
           d : in  STD_LOGIC_VECTOR (31 downto 0);
           sync_reset : in  STD_LOGIC;
           q : out  STD_LOGIC_VECTOR (31 downto 0));
end Biestable_D;

architecture Behavioral of Biestable_D is

begin

process (async_reset,en,clk,d,sync_reset)
begin
   if async_reset ='1' then   
      q <= X"00000000";
   elsif (clk'event and clk='1') then 
      if sync_reset = '1' then 
         q<= X"00000000";
			elsif en = '1'	then		
			  q<=d;
		end if; 
   end if;
end process;

end Behavioral;