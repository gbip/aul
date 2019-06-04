library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- these librairies must be included
-- they enable to include functions necessaries
-- to read string from a file and convert them into an array of
-- std_logic_vector
use std.textio.all;
use ieee.std_logic_textio.all;

package common is

	-- HERE: those values depend on your own choice during compilation
	-- LEN_SEL enables you to choose how much instruction your instruction memory (rom) can store
	-- LEN_INSTR enables you to choose the length of one instruction, in my case an instruction has
	-- this structure: OP_CODE A B C, each part is stored on one 1 byte (8 bits) so I need 32 bits to
	-- store an instruction
	-- maybe some of you have instruction with two operands: OP_CODE A B, you will need 24 bits to
	-- store an instruction, so you will have to adjust LEN_INSTR
   -- change the size of the bus according to the size of your instruction
	constant LEN_SEL: natural := 16;
	constant LEN_INSTR: natural := 48;
	constant NOP : STD_LOGIC_VECTOR(47 downto 0) := x"170000000000";

	type instrArray is array(0 to 2**LEN_SEL-1) of std_logic_vector(LEN_INSTR-1 downto 0);
	
	type instr is record
		opcode : STD_LOGIC_VECTOR (7 downto 0);
		reg : STD_LOGIC_VECTOR (7 downto 0);
		val : STD_LOGIC_VECTOR (31 downto 0);
	end record instr;
	
	type p_early is record 
		opcode : STD_LOGIC_VECTOR (7 downto 0);
		reg : STD_LOGIC_VECTOR (7 downto 0);
		val : STD_LOGIC_VECTOR (31 downto 0);
		d1 :  STD_LOGIC_VECTOR (31 downto 0);
		d2 : STD_LOGIC_VECTOR (31 downto 0);
		pc : STD_LOGIC_VECTOR (31 downto 0);
	end record p_early;
	
	type p_late is record
		opcode: STD_LOGIC_VECTOR (7 downto 0);
      reg: STD_LOGIC_VECTOR (7 downto 0);
      val: STD_LOGIC_VECTOR (31 downto 0);
		d1: STD_LOGIC_VECTOR (31 downto 0);
		d2: STD_LOGIC_VECTOR (31 downto 0);
      flags:  STD_LOGIC_VECTOR (3 downto 0);
      ual_output: STD_LOGIC_VECTOR (31 downto 0);
	end record p_late;
	
	type p_last is record
		opcode : STD_LOGIC_VECTOR (7 downto 0);
      firstOperand : STD_LOGIC_VECTOR (7 downto 0);
      ual_readValue : STD_LOGIC_VECTOR (31 downto 0);
		mem_readValue : STD_LOGIC_VECTOR (31 downto 0);
		dataOperand : STD_LOGIC_VECTOR (31 downto 0) ;
		firstRegData : STD_LOGIC_VECTOR (31 downto 0);
		secondRegData : STD_LOGIC_VECTOR (31 downto 0) ;
	end record p_last;
	
	type amu_interface is record 
		instr_1 : instr;
		instr_2 : instr;
		instr_3 : instr;
		instr_4 : instr;
	end record amu_interface;
	
	-- the "impure" keyword is important, in VHDL, functions by default are "pure" meaning that
	-- the result is computed using only the function parameters
	-- the "impure" keyword enables to specify that the result of a function depends not only of its input
	-- the function can have side effects because of Input/Outpout operations
	impure function init_rom(filename: string) return instrArray;

end package;



package body common is


	impure function init_rom(filename: string) return instrArray is
		file file_ptr: text;

		-- the rom is initialised with 1 because in my code an instruction filled with 1 does nothing  
		-- it is a NOP (no operation), so the remaining instructions can't change the state of memories
		variable rom: instrArray := (others => (others => '1'));
		variable f_line: line;
		variable slv_v: std_logic_vector(LEN_INSTR-1 downto 0);
		variable lines_read: integer := 0;
	begin
		file_open(file_ptr, filename, READ_MODE);

		while (not endfile(file_ptr)) loop
			-- a line is read from file_ptr
			readline(file_ptr, f_line);

			-- the line is converted into a std_logic_vector
			hread(f_line, slv_v);

			-- the std_logic_vector is assigned into memory
			rom(lines_read) := slv_v;

			lines_read := lines_read + 1;
		end loop;

		file_close(file_ptr);

		return rom;
	end function;

end common;


