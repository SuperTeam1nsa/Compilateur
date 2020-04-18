library IEEE;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.STD_LOGIC_1164.ALL;


entity UAL is
    Port ( A : in  STD_LOGIC_VECTOR (7 downto 0);
           B : in  STD_LOGIC_VECTOR (7 downto 0);
           Ctrl_Alu : in  STD_LOGIC_VECTOR (2 downto 0);
           S : out  STD_LOGIC_VECTOR (7 downto 0);
           Flags : out  STD_LOGIC_VECTOR (3 downto 0));
--Le sens des flèches N,O,Z,C sont sortant de UAL; Ctrl_Alu sont entrant de UAL)

end UAL;

architecture Behavioral of UAL is
signal --Ctrl_Alu est un signal ?
	
begin
	

end Behavioral;
