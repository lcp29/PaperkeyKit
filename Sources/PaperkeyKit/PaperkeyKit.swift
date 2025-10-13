//
//  PaperkeyKit.swift
//  PaperkeyKit
//
//  Created by helmholtz on 2025/10/13.
//

import Darwin
import Foundation
import CPaperkey

class Paperkey {
    enum DataType {
        case AUTO
        case RAW
        case BASE16
    }
    
    /*
     int extract(struct stream *input, struct stream *output,
                 enum data_type output_type, unsigned int output_width);
     */
    
    static func extract(input: Data, outputType: DataType, outputWidth: UInt) -> Data? {
        if input.isEmpty { return nil }
        
        guard let outputStream = create_empty_stream() else { return nil }
        
        let outputTypeC: data_type = switch outputType {
            case .AUTO: AUTO
            case .RAW: RAW
            case .BASE16: BASE16
        }
        
        let result = input.withUnsafeBytes { (inputBuffer: UnsafeRawBufferPointer) in
            var inputStream = stream(
                buffer: UnsafeMutableRawPointer(mutating: inputBuffer.baseAddress!).assumingMemoryBound(to: UInt8.self),
                size: CInt(input.count),
                pos: 0,
                memsize: CInt(input.count)
            )
            return CPaperkey.extract(&inputStream, outputStream, outputTypeC, CUnsignedInt(outputWidth))
        }
        
        defer {
            outputStream.pointee.buffer.deallocate()
            outputStream.deallocate()
        }
        
        if result != 0 { return nil }
        
        return Data(bytes: outputStream.pointee.buffer, count: Int(outputStream.pointee.size))
    }
    
    /*
     int restore(struct stream *pubring, struct stream *secrets,
                 enum data_type input_type, struct stream *output,
                 unsigned int output_width, int ignore_crc_error);
     */
}
