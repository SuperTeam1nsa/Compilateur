--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   18:58:31 05/21/2020
-- Design Name:   
-- Module Name:   /home/hsahraou/Bureau/4A/COMPILATEUR/Compilateur/Compilateur/VHDL/Processeur/Processeur/Test_donneesmemoires.vhd
-- Project Name:  Processeur
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: donnessmemoire
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
 
ENTITY Test_donneesmemoires IS
END Test_donneesmemoires;
 
ARCHITECTURE behavior OF Test_donneesmemoires IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT donnessmemoire
    PORT(
         Add : IN  std_logic_vector(7 downto 0);
         INS : IN  std_logic_vector(7 downto 0);
         RW : IN  std_logic;
         RST : IN  std_logic;
         CLK : IN  std_logic;
         OUTS : OUT  std_logic_vector(7 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal Add : std_logic_vector(7 downto 0) := (others => '0');
   signal INS : std_logic_vector(7 downto 0) := (others => '0');
   signal RW : std_logic := '0';
   signal RST : std_logic := '0';
   signal CLK : std_logic := '0';

 	--Outputs
   signal OUTS : std_logic_vector(7 downto 0);

   -- Clock period definitions
   constant CLK_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: donnessmemoire PORT MAP (
          Add => Add,
          INS => INS,
          RW => RW,
          RST => RST,
          CLK => CLK,
          OUTS => OUTS
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
 --  stim_proc: process
  -- begin		
      -- hold reset state for 100 ns.
  --    wait for 100 ns;	

    --  wait for CLK_period*10;

      -- insert stimulus here 

      --wait;
  -- end process;

END;
