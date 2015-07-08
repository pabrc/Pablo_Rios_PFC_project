library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

---- Uncomment the following library declaration if instantiating
---- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity Detector_Flancos is
    Port ( clk : in  STD_LOGIC;
           reset : in  STD_LOGIC;
           input : in  STD_LOGIC;
           out_falling_edge : out  STD_LOGIC;
           out_rising_edge : out  STD_LOGIC);
    end Detector_Flancos;

architecture Behavioral of Detector_Flancos is

COMPONENT Biestable_Det
    Port ( async_reset : in  STD_LOGIC;
           ce : in  STD_LOGIC;
           clk : in  STD_LOGIC;
           d : in  STD_LOGIC;
           sync_reset : in  STD_LOGIC;
           q : out  STD_LOGIC);
	END COMPONENT;
	
	COMPONENT nand_2
    Port ( a : in  STD_LOGIC;
           b : in  STD_LOGIC;
           c : out  STD_LOGIC);
	END COMPONENT;
	

signal l1, l2 : std_logic;  


begin


	Inst_biestable_d1: Biestable_Det PORT MAP(
		d => l2,
		clk => clk,
		async_reset => reset,
		q => l1,
		sync_reset => '0',
		ce =>'1'
		);
	
	Inst_biestable_d2: Biestable_Det PORT MAP(
		d => input,
		async_reset => reset ,
		clk => clk,
	   q => l2,
		sync_reset => '0',
		ce => '1'
	);
	
	Inst_nand_2a: nand_2 PORT MAP(
		a => l1,
		b => l2,
		c => out_falling_edge
	);
	
	Inst_nand_2b: nand_2 PORT MAP(
		a => l2,
		b => l1,
		c => out_rising_edge
	);


end Behavioral;



