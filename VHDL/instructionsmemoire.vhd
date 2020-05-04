--OK

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity instructionsmemoire is
Port ( Add : in  STD_LOGIC_VECTOR (7 downto 0);
       CLK : in  STD_LOGIC;
       OUTS : out  STD_LOGIC_VECTOR (31 downto 0)); --OUT pas possible

end instructionsmemoire;

architecture Behavioral of instructionsmemoire is
--Meme methode que le banc de registre
type memoiretableau is array (integer range 255 downto 0) of STD_LOGIC_VECTOR(31 downto 0);
signal instmemoire : memoiretableau := (others => (others => '0'));
--:= ( "10000000000000001000000000000000","10000000000000001000000000000000",...,""); #codeOperation operandeA OperandeB OperandeC: 8x4=32

begin
--Comme pour la mémoire des données, la lecture se fera synchrone avec l'horloge CLK.
	process
	begin
		wait until CLK'event and CLK='1';
		
		OUTS <= instmemoire(to_integer(unsigned(Add)));
		
	end process;

end Behavioral;