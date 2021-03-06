USE [master]
GO
/****** Object:  Database [bitcoin1]    Script Date: 25/06/2022 8:55:29 am ******/
CREATE DATABASE [bitcoin1]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'bitcoin1', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL15.MSSQLSERVER\MSSQL\DATA\bitcoin1.mdf' , SIZE = 8192KB , MAXSIZE = UNLIMITED, FILEGROWTH = 65536KB )
 LOG ON 
( NAME = N'bitcoin1_log', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL15.MSSQLSERVER\MSSQL\DATA\bitcoin1_log.ldf' , SIZE = 8192KB , MAXSIZE = 2048GB , FILEGROWTH = 65536KB )
 WITH CATALOG_COLLATION = DATABASE_DEFAULT
GO
ALTER DATABASE [bitcoin1] SET COMPATIBILITY_LEVEL = 150
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [bitcoin1].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [bitcoin1] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [bitcoin1] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [bitcoin1] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [bitcoin1] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [bitcoin1] SET ARITHABORT OFF 
GO
ALTER DATABASE [bitcoin1] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [bitcoin1] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [bitcoin1] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [bitcoin1] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [bitcoin1] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [bitcoin1] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [bitcoin1] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [bitcoin1] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [bitcoin1] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [bitcoin1] SET  ENABLE_BROKER 
GO
ALTER DATABASE [bitcoin1] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [bitcoin1] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [bitcoin1] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [bitcoin1] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [bitcoin1] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [bitcoin1] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [bitcoin1] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [bitcoin1] SET RECOVERY FULL 
GO
ALTER DATABASE [bitcoin1] SET  MULTI_USER 
GO
ALTER DATABASE [bitcoin1] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [bitcoin1] SET DB_CHAINING OFF 
GO
ALTER DATABASE [bitcoin1] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [bitcoin1] SET TARGET_RECOVERY_TIME = 60 SECONDS 
GO
ALTER DATABASE [bitcoin1] SET DELAYED_DURABILITY = DISABLED 
GO
ALTER DATABASE [bitcoin1] SET ACCELERATED_DATABASE_RECOVERY = OFF  
GO
EXEC sys.sp_db_vardecimal_storage_format N'bitcoin1', N'ON'
GO
ALTER DATABASE [bitcoin1] SET QUERY_STORE = OFF
GO
USE [bitcoin1]
GO
/****** Object:  Table [dbo].[Walet]    Script Date: 25/06/2022 8:55:29 am ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Walet](
	[wallet_id] [int] NULL,
	[coin_id] [varchar](30) NULL,
	[coin_amount] [int] NULL
) ON [PRIMARY]
GO
/****** Object:  View [dbo].[waletview]    Script Date: 25/06/2022 8:55:29 am ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE VIEW [dbo].[waletview] AS 
select wallet_id,coin_id 
from walet
GO
/****** Object:  Table [dbo].[authenticate]    Script Date: 25/06/2022 8:55:29 am ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[authenticate](
	[pass_word] [varchar](30) NULL,
	[cus_id] [int] NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[coin]    Script Date: 25/06/2022 8:55:29 am ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[coin](
	[coin_id] [varchar](30) NOT NULL,
	[coin_name] [varchar](30) NULL,
	[coin_price] [varchar](30) NULL,
	[change_rate] [varchar](30) NULL,
PRIMARY KEY CLUSTERED 
(
	[coin_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[customer]    Script Date: 25/06/2022 8:55:29 am ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[customer](
	[cus_id] [int] NOT NULL,
	[username] [varchar](30) NULL,
PRIMARY KEY CLUSTERED 
(
	[cus_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[waltet_main]    Script Date: 25/06/2022 8:55:29 am ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[waltet_main](
	[wallet_id] [int] NOT NULL,
	[totalbalance] [int] NULL,
PRIMARY KEY CLUSTERED 
(
	[wallet_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
ALTER TABLE [dbo].[waltet_main] ADD  DEFAULT ((100)) FOR [totalbalance]
GO
ALTER TABLE [dbo].[authenticate]  WITH CHECK ADD FOREIGN KEY([cus_id])
REFERENCES [dbo].[customer] ([cus_id])
GO
ALTER TABLE [dbo].[Walet]  WITH CHECK ADD FOREIGN KEY([coin_id])
REFERENCES [dbo].[coin] ([coin_id])
GO
ALTER TABLE [dbo].[Walet]  WITH CHECK ADD FOREIGN KEY([wallet_id])
REFERENCES [dbo].[waltet_main] ([wallet_id])
GO
/****** Object:  StoredProcedure [dbo].[p_getprice]    Script Date: 25/06/2022 8:55:29 am ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

create procedure [dbo].[p_getprice]
as 
select * from coin
GO
/****** Object:  StoredProcedure [dbo].[pp]    Script Date: 25/06/2022 8:55:29 am ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
create procedure [dbo].[pp]
@name varchar(30), @coin float
as
select * from coin
go;
GO
USE [master]
GO
ALTER DATABASE [bitcoin1] SET  READ_WRITE 
GO
