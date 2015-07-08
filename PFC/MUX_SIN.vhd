  library IEEE;
  use IEEE.STD_LOGIC_1164.all;
 
     ENTITY mux_sin IS
        PORT(sel    : IN std_logic_vector(5 DOWNTO 0); 
				 en	  : IN std_logic;
             salida : OUT std_logic_vector(31 DOWNTO 0));
     END mux_sin;
 
     ARCHITECTURE synth OF mux_sin IS
     BEGIN
		
       PROCESS (sel,en) IS
       BEGIN
		 
			IF en='0' then
				salida<=x"00000000";
			else
			
         CASE sel IS
           WHEN "000000" => salida <= x"00007FFF";
           WHEN "000001" => salida <= x"00009639";
           WHEN "000010" => salida <= x"0000ABC6";
           WHEN "000011" => salida <= x"0000BFFE";
			  WHEN "000100" => salida <= x"0000D245";
           WHEN "000101" => salida <= x"0000E20C";
           WHEN "000110" => salida <= x"0000EED8";
           WHEN "000111" => salida <= x"0000F846";
			  WHEN "001000" => salida <= x"0000FE0C";
           WHEN "001001" => salida <= x"0000FFFE";
           WHEN "001010" => salida <= x"0000FE0C";
           WHEN "001011" => salida <= x"0000F846";
			  WHEN "001100" => salida <= x"0000EED8";
           WHEN "001101" => salida <= x"0000E20C";
           WHEN "001110" => salida <= x"0000D245";
           WHEN "001111" => salida <= x"0000BFFE";
			  WHEN "010000" => salida <= x"0000ABC6";
           WHEN "010001" => salida <= x"00009639";
           WHEN "010010" => salida <= x"00007FFF";
           WHEN "010011" => salida <= x"000069C5";
			  WHEN "010100" => salida <= x"00005438";
           WHEN "010101" => salida <= x"00003FFF";
           WHEN "010110" => salida <= x"00002DB9";
           WHEN "010111" => salida <= x"00001DF2";
			  WHEN "011000" => salida <= x"00001126";
           WHEN "011001" => salida <= x"000007B8";
           WHEN "011010" => salida <= x"000001F2";
           WHEN "011011" => salida <= x"00000000";
			  WHEN "011100" => salida <= x"000001F2";
           WHEN "011101" => salida <= x"000007B8";
           WHEN "011110" => salida <= x"00001126";
           WHEN "011111" => salida <= x"00001DF2";
			  WHEN "100000" => salida <= x"00002DB9";
           WHEN "100001" => salida <= x"00003FFF";
           WHEN "100010" => salida <= x"00005438";
           WHEN "100011" => salida <= x"000069C5";
           WHEN OTHERS => salida <= x"00000000";
         END CASE;
		 END IF;
       END PROCESS;
     END synth;