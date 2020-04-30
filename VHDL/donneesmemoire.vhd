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

entity donnessmemoire is
Port (  Add : in  STD_LOGIC_VECTOR (7 downto 0);
        INS : in  STD_LOGIC_VECTOR (7 downto 0); --IN pas possible
        RW : in  STD_LOGIC; 
        RST : in  STD_LOGIC;
        CLK : in  STD_LOGIC;
        OUTS : out  STD_LOGIC_VECTOR (7 downto 0)); --OUT pas possible

end donnessmemoire;

architecture Behavioral of donnessmemoire is
--Meme methode que la memoire d'instruction
type memoiretableau is array (integer range 255 downto 0) of STD_LOGIC_VECTOR(7 downto 0);
signal donnmemoire : memoiretableau := (others => (others => '0'));

begin


-- Dans le cas d'une écriture, le contenu de l'entrée IN est copié dans la mémoire à l'adresse @


	process
	begin --la lecture, l'écriture et le reset  se fera synchrone avec l'horloge CLK.
		wait until CLK'event and CLK='1';

-- Le reset, RST, permettra d'initialiser le contenu de la mémoire à 0x00
		if RST='0' then
				donnmemoire <= (others=>(others=>'0'));
			else	
-- Pour réaliser une lecture, RW doit être positionné à 1 et pour réaliser une écriture, RW doit être positionné à 0
				if RW='0' then
				-- Dans le cas d'une écriture, le contenu de l'entrée IN est copié dans la mémoire à l'adresse @
					donnmemoire(to_integer(unsigned(Add))) <= INS;
				else 
					OUTS <= donnmemoire(to_integer(unsigned(Add)));
				end if;				
			end if;
		
	end process;

end Behavioral;