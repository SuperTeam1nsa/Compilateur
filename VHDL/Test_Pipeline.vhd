--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   18:59:45 05/21/2020
-- Design Name:   
-- Module Name:   /home/hsahraou/Bureau/4A/COMPILATEUR/Compilateur/Compilateur/VHDL/Processeur/Processeur/Test_Pipeline.vhd
-- Project Name:  Processeur
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: pipeline1
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY Test_Pipeline IS
END Test_Pipeline;
 
ARCHITECTURE behavior OF Test_Pipeline IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT pipeline1
    PORT(
         CLK : IN  std_logic;
         OP : IN  std_logic_vector(7 downto 0);
         A : IN  std_logic_vector(7 downto 0);
         B : IN  std_logic_vector(7 downto 0);
         C : IN  std_logic_vector(7 downto 0);
         OOP : OUT  std_logic_vector(7 downto 0);
         OA : OUT  std_logic_vector(7 downto 0);
         OB : OUT  std_logic_vector(7 downto 0);
         OC : OUT  std_logic_vector(7 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal CLK : std_logic := '0';
   signal OP : std_logic_vector(7 downto 0) := (others => '0');
   signal A : std_logic_vector(7 downto 0) := (others => '0');
   signal B : std_logic_vector(7 downto 0) := (others => '0');
   signal C : std_logic_vector(7 downto 0) := (others => '0');

 	--Outputs
   signal OOP : std_logic_vector(7 downto 0);
   signal OA : std_logic_vector(7 downto 0);
   signal OB : std_logic_vector(7 downto 0);
   signal OC : std_logic_vector(7 downto 0);

   -- Clock period definitions
   constant CLK_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: pipeline1 PORT MAP (
          CLK => CLK,
          OP => OP,
          A => A,
          B => B,
          C => C,
          OOP => OOP,
          OA => OA,
          OB => OB,
          OC => OC
        );

   -- Clock process definitions
   CLK_process :process
   begin
		CLK <= '0';
		wait for CLK_period/2;
		CLK <= '1';
		wait for CLK_period/2;
   end process;
 

   -- Stimulus process
--   stim_proc: process
--   begin		
      -- hold reset state for 100 ns.
 --     wait for 100 ns;	

 --     wait for CLK_period*10;

      -- insert stimulus here 

  --    wait;
 --  end process;

END;
