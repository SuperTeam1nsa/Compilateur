library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE IEEE.NUMERIC_STD.ALL;

entity bancregistre is
    Port ( A : in  STD_LOGIC_VECTOR (3 downto 0);
           B : in  STD_LOGIC_VECTOR (3 downto 0);
           addW : in  STD_LOGIC_VECTOR (3 downto 0);
           W : in  STD_LOGIC;  
           Data : in  STD_LOGIC_VECTOR (7 downto 0);
           RST : in  STD_LOGIC;  
           CLK : in  STD_LOGIC;
           QA : out  STD_LOGIC_VECTOR (7 downto 0);
           QB : out  STD_LOGIC_VECTOR (7 downto 0)
			  );
end bancregistre;

architecture Behavioral of bancregistre is


begin

	
end Behavioral;
