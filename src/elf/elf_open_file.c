/*
** elf_open_file.c for open  in /src/elf/
**
** Made by Frederic Oddou
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Tue Apr 11 22:57:08 2017 Frederic Oddou
** Last update Fri Apr 21 11:35:34 2017 Frederic Oddou
*/

#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "strace.h"

void			get_symval(t_core		*core)
{
  unsigned int		i;
  unsigned int		id;
  Elf64_Sym		*symtab;
  char			*symstr;

  i = id = 0;
  if (core->elf.symshdr == NULL)
    return ;
  symtab = GET_SYMTAB(core->elf.symshdr);
  symstr = GET_STRTAB(core->elf.symshdr);
  core->elf.symval = calloc(1, sizeof(t_elf_value) *
			    (SIZE_SYM(core->elf.symshdr) + 1));
  while (i < SIZE_SYM(core->elf.symshdr))
    {
      if (ELF64_ST_TYPE(symtab->st_info) == STT_FUNC && symtab->st_value)
	{
	  core->elf.symval[id].name = &symstr[symtab->st_name];
	  core->elf.symval[id].value = symtab->st_value;
	  id++;
	  memset(&core->elf.symval[id], 0, sizeof(t_elf_value));
	}
      symtab++;
      i++;
    }
}

void			get_dynval(t_core		*core)
{
  unsigned int		i;
  unsigned int		id;
  Elf64_Sym		*symtab;
  char			*symstr;

  i = id = 0;
  if (core->elf.dynshdr == NULL)
    return ;
  symtab = GET_SYMTAB(core->elf.dynshdr);
  symstr = GET_STRTAB(core->elf.dynshdr);
  core->elf.dynval = calloc(1, sizeof(t_elf_value) *
			    (SIZE_SYM(core->elf.dynshdr) + 1));
  while (i < SIZE_SYM(core->elf.dynshdr))
    {
      if (ELF64_ST_TYPE(symtab->st_info) == STT_FUNC)
	{
	  core->elf.dynval[id].name = &symstr[symtab->st_name];
	  core->elf.dynval[id].value = core->elf.pltaddr + (16 * (id + 1));
	  id++;
	  memset(&core->elf.dynval[id], 0, sizeof(t_elf_value));
	}
      symtab++;
      i++;
    }
}

static bool		check_if_elf(t_core		*core)
{
  int			i;
  char			*section_str;

  i = -1;
  ((char *)core->elf.ehdr)[core->elf.size] = 0;
  if (memcmp(core->elf.ehdr->e_ident, ELFMAG, strlen(ELFMAG)))
      return (false + 0 * fprintf(stderr, "File format not recognized.\n"));
  core->elf.shdr = (Elf64_Shdr *)((char *)core->elf.ehdr +
		    core->elf.ehdr->e_shoff);
  section_str = ((char *)core->elf.ehdr +
		 core->elf.shdr[core->elf.ehdr->e_shstrndx].sh_offset);
  while (++i < core->elf.ehdr->e_shnum)
    {
      if (core->elf.shdr[i].sh_type == SHT_SYMTAB)
	core->elf.symshdr = ((Elf64_Shdr *)&(core->elf.shdr[i]));
      else if (core->elf.shdr[i].sh_type == SHT_DYNSYM)
	core->elf.dynshdr = ((Elf64_Shdr *)&(core->elf.shdr[i]));
      else if (!strcmp(&section_str[core->elf.shdr[i].sh_name], ".plt"))
	core->elf.pltaddr = core->elf.shdr[i].sh_addr;
    }
  get_symval(core);
  get_dynval(core);
  return (true);
}

static bool	get_ehdr(t_core			*core,
			 int			fd)
{
  if ((core->elf.size = lseek(fd, 0, SEEK_END)) == -1 ||
      lseek(fd, 0, SEEK_SET) == -1)
    {
      perror("lseek");
      return (false);
    }
  if (core->elf.size < (int)sizeof(Elf64_Ehdr))
    {
      fprintf(stderr, "File format not recognized.\n");
      return (false);
    }
  if (!(core->elf.ehdr = calloc(1, core->elf.size + 1)))
    {
      fprintf(stderr, "calloc failed.\n");
      return (false);
    }
  if (read(fd, core->elf.ehdr, core->elf.size) != core->elf.size)
    {
      perror("read");
      return (false);
    }
  return (true);
}

bool			elf_open_file(t_core *core)
{
  int			fd;
  struct stat		buf;

  if ((fd = open(core->bin_path, O_RDONLY)) < 0)
    {
      perror("open");
      return (false);
    }
  if (fstat(fd, &buf) || S_ISDIR(buf.st_mode) ||
      !get_ehdr(core, fd) ||
      !check_if_elf(core))
    {
      close(fd);
      fprintf(stderr, "File error.\n");
      return (false);
    }
  close(fd);
  return (true);
}
