{-# LANGUAGE AlternativeLayoutRule #-}

module AlphaHeavy.XPathParsers
  ( evaluateHTMLXPath
  , parseHTMLBodyText
  , evaluateHTMLXPathContents
  , evaluateHTMLXPathRemove
  ) where

import Bindings.XPathParsers (c'htmlEvalXPath, c'htmlGetText, c'htmlEvalXPathContents, c'htmlEvalXPathRemove)
import Control.Exception (finally)
import Foreign.C.Error (throwErrnoIfMinus1_)
import Foreign.C.String (withCString)
import Foreign.Marshal.Alloc (alloca, free)
import Foreign.Storable (peek)
import Data.Text.Encoding (decodeUtf8)
import qualified Data.ByteString as B
import qualified Data.ByteString.Unsafe as B
import qualified Data.Text as T

parseHTMLBodyText :: String -> B.ByteString -> IO T.Text
parseHTMLBodyText uri input = B.unsafeUseAsCStringLen input go where
  go (str, len) = withCString uri $ \ uri' -> do
    alloca $ \ bufferPtr -> do
    alloca $ \ bufferLen -> do 
      throwErrnoIfMinus1_ "htmlGetText" $ c'htmlGetText uri' str (fromIntegral len) bufferPtr bufferLen
      bufferPtr' <- peek bufferPtr
      bufferLen' <- peek bufferLen
      bs <- B.packCStringLen (bufferPtr', fromIntegral bufferLen') `finally` free bufferPtr'
      return . decodeUtf8 $ bs

evaluateHTMLXPath :: String -> String -> B.ByteString -> IO T.Text
evaluateHTMLXPath xpath uri input = B.unsafeUseAsCStringLen input go where
  go (str, len) =
    withCString xpath $ \ xpath' -> do
    withCString uri $ \ uri' -> do
    alloca $ \ bufferPtr -> do
    alloca $ \ bufferLen -> do 
      throwErrnoIfMinus1_ "htmlEvalXPath" $ c'htmlEvalXPath xpath' uri' str (fromIntegral len) bufferPtr bufferLen
      bufferPtr' <- peek bufferPtr
      bufferLen' <- peek bufferLen
      bs <- B.packCStringLen (bufferPtr', fromIntegral bufferLen') `finally` free bufferPtr'
      return . decodeUtf8 $ bs

evaluateHTMLXPathContents :: String -> String -> B.ByteString -> IO T.Text
evaluateHTMLXPathContents xpath uri input = B.unsafeUseAsCStringLen input go where
  go (str, len) =
    withCString xpath $ \ xpath' -> do
    withCString uri $ \ uri' -> do
    alloca $ \ bufferPtr -> do
    alloca $ \ bufferLen -> do 
      throwErrnoIfMinus1_ "htmlEvalXPathContents" $ c'htmlEvalXPathContents xpath' uri' str (fromIntegral len) bufferPtr bufferLen
      bufferPtr' <- peek bufferPtr
      bufferLen' <- peek bufferLen
      bs <- B.packCStringLen (bufferPtr', fromIntegral bufferLen') `finally` free bufferPtr'
      return . decodeUtf8 $ bs

evaluateHTMLXPathRemove :: String -> String -> B.ByteString -> IO T.Text
evaluateHTMLXPathRemove xpath uri input = B.unsafeUseAsCStringLen input go where
  go (str, len) =
    withCString xpath $ \ xpath' -> do
    withCString uri $ \ uri' -> do
    alloca $ \ bufferPtr -> do
    alloca $ \ bufferLen -> do 
      throwErrnoIfMinus1_ "htmlEvalXPathRemove" $ c'htmlEvalXPathRemove xpath' uri' str (fromIntegral len) bufferPtr bufferLen
      bufferPtr' <- peek bufferPtr
      bufferLen' <- peek bufferLen
      bs <- B.packCStringLen (bufferPtr', fromIntegral bufferLen') `finally` free bufferPtr'
      return . decodeUtf8 $ bs
